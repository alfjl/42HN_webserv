#include "routing.hpp"

#include "../../pal/fork/fork.hpp"
#include "../../pal/fs/fs.hpp"
#include "../../http/handler/http_handler.hpp"
#include "../../http/handler/cgi_handler.hpp"
#include "../../http/proto/cgi_msg.hpp"
#include "../../http/proto/response.hpp"
#include "../../http/proto/request.hpp"
#include "../filesystem/filesystem.hpp"
#include "../instance.hpp"

#include "pages/pages.hpp"
#include "table/routing_table.hpp"

namespace webserv {
    namespace core {

        routing::routing(instance& the_inst, webserv::http::http_handler& the_http_handler, webserv::http::request& the_request) : instance_component(the_inst), _recursion_count(0), _the_http_handler(the_http_handler), _the_request(the_request), _component_pages(*this), _component_http(*this), _component_cgi(*this) {

        }

        routing::~routing() {

        }

        routing_table& routing::get_table() { return get_instance().get_routing_table(); }

        unsigned int   routing::get_recursion_count() { return _recursion_count; }

        webserv::http::http_handler&    routing::get_http_handler() { return _the_http_handler; }
        webserv::http::request&         routing::get_request() { return _the_request; }
        webserv::http::response_fixed&  routing::get_response() { return _the_response; }

        routing_component_pages&        routing::get_component_pages() { return _component_pages; }
        routing_component_http&         routing::get_component_http() { return _component_http; }
        routing_component_cgi&          routing::get_component_cgi()  { return _component_cgi;  }

        void routing::handle_http_head(route& route) {
            get_component_http().handle_head(route);
        }

        void routing::handle_http_get(route& route) {
            get_component_http().handle_get(route);
        }

        void routing::handle_http_post(route& route) {
            get_component_http().handle_post(route);
        }

        void routing::handle_http_delete(route& route) {
            get_component_http().handle_delete(route);
        }
        
        void routing::handle_cgi(cgi_route& the_route) {
            get_component_cgi().handle_cgi(the_route);
        }

        void routing::error_page(unsigned int code) {
            get_component_pages().error_page(code);
        }

        void routing::look_up() {
            route* the_route = get_table().query(get_request().get_line().get_uri().get_path());

            follow_route(the_route);
        }

        void routing::_follow_route(route* the_route) {
            unsigned int code;

            if (get_request().get_line().get_method() == webserv::http::http_method__invalid) {
                error_page(400);
            } else if (!the_route->is_method_allowed(get_request().get_line().get_method())) {
                error_page(405);
            } else if (the_route->is_cgi()) {
                handle_cgi((cgi_route&) *the_route);
                delete the_route;
                return;
            } else if (the_route->is_redirection()) {
                temporary_redirect_302(get_response(), the_route->get_file_target());
            } else if (the_route->is_permanent_redirection()) {
                permanent_redirect_301(get_response(), the_route->get_file_target());
            } else if (the_route->is_error(code)) {
                error_page(code);
            } else if (the_route->get_max_body().enabled() && get_request().get_body().size() > the_route->get_max_body().value()) {
                error_page(413);
            } else {
                switch (get_request().get_line().get_method()) {
                    case webserv::http::http_method_head: { handle_http_head(*the_route); break; }
                    case webserv::http::http_method_get: { handle_http_get(*the_route); break; }
                    case webserv::http::http_method_put:
                    case webserv::http::http_method_post: { handle_http_post(*the_route); break; }
                    case webserv::http::http_method_delete: { handle_http_delete(*the_route); break; }
                    default: {
                        error_page(418);
                        break;
                    }
                }
            }

            delete the_route;
            get_response().write(*get_http_handler().get_connection());
        }

        void routing::follow_route(route* the_route) {
            try {
                _recursion_count++;
                _follow_route(the_route);
                _recursion_count--;
            } catch (std::exception& e) {
                _recursion_count--;
                throw;
            }
        }

        void routing::error_and_flush(unsigned int code) {
            error_page(code);
            get_response().write(*get_http_handler().get_connection());
        }

    }
}
