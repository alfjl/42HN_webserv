#include "routing.hpp"

#include "pages/pages.hpp"
#include "cgi/cgi.hpp"
#include "../../pal/fork/fork.hpp"
#include "../../pal/fs/fs.hpp"
#include "../../http/handler/http_handler.hpp"
#include "../../http/handler/cgi_handler.hpp"
#include "../../http/proto/cgi_msg.hpp"
#include "../../http/proto/response.hpp"
#include "../../http/proto/request.hpp"
#include "../filesystem/filesystem.hpp"
#include "../instance.hpp"

#include "table/routing_table.hpp"

namespace webserv {
    namespace core {

        routing::routing(instance& the_inst, webserv::http::http_handler& the_http_handler, webserv::http::request& the_request) : instance_component(the_inst), _the_http_handler(the_http_handler), _the_request(the_request), _component_http(*this), _component_cgi(*this) {

        }

        routing::~routing() {

        }

        routing_table& routing::get_table() { return get_instance().get_routing_table(); }


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
        
        void routing::handle_cgi(cgi_route* the_route) {
            get_component_cgi().handle_cgi(*the_route);
        }

        void routing::error_page(unsigned int code) {
            // TODO, FIXME, XXX: Watch out for recursion!
            route* the_route = get_table().query_error_page(code);
            if (the_route == NULL) {
                error_code(get_response(), code);
                get_response().write(*get_http_handler().get_connection());
            } else {
                follow_route(the_route);
            }
        }

        void routing::look_up() {
            route* the_route = get_table().query(get_request().get_line().get_uri().get_path());

            follow_route(the_route);
        }

        void routing::follow_route(route* the_route) {
            int code;

            if (!the_route->is_method_allowed(get_request().get_line().get_method())) {
                delete the_route;
                error_page(405);
                return;
            } else if (the_route->is_cgi()) { // TODO: Does this always return false?
                handle_cgi((cgi_route*) the_route);
                delete the_route;
                return; // Invisible yield
            } else if (the_route->is_redirection()) {
                temporary_redirect_302(get_response(), the_route->get_file_target());
            } else if (the_route->is_permanent_redirection()) {
                permanent_redirect_301(get_response(), the_route->get_file_target());
            } else if (the_route->is_error(code)) {
                delete the_route;
                error_page(code);
                return;
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
                        teapot_418(get_response());
                        break;
                    }
                }
            }

            delete the_route;
            get_response().write(*get_http_handler().get_connection());
        }

    }
}
