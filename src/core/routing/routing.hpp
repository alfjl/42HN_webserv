#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/proto/response.hpp"
#include "../../http/proto/request.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"
#include "../../pal/fs/fs.hpp"

#include "table/routing_table.hpp"

namespace webserv {
    namespace http { class http_handler; }

    namespace core {

        class   selector;

        class routing : public component {
            webserv::core::routing_table table;

        public:
            routing(instance& the_inst);
            ~routing();

            routing_table& get_table();

            void look_up(webserv::http::request& request, webserv::http::http_handler* the_http_handler);

            void tick();

        protected:
            void error_page(webserv::http::response_fixed& response, webserv::http::request& request, webserv::http::http_handler* the_http_handler, unsigned int code);
            void follow_route(webserv::http::response_fixed& response, webserv::http::request& request, route* route, webserv::http::http_handler* the_http_handler);

            void handle_http_head(webserv::http::response_fixed& response, webserv::http::request& request, route& route);
            void handle_http_get(webserv::http::response_fixed& response, webserv::http::request& request, route& route);
            void handle_http_post(webserv::http::response_fixed& response, webserv::http::request& request, route& route);
            void handle_http_delete(webserv::http::response_fixed& response, webserv::http::request& request, route& route);

            void handle_cgi(webserv::http::response_fixed& response, webserv::http::request& request, route* route, webserv::http::http_handler* the_http_handler);

            void set_response_code(webserv::util::path file_path, webserv::http::response_fixed& response);
            void get_request_body(webserv::util::path file_path, webserv::http::response_fixed& response, webserv::http::request& request);
            void put_http_handler_to_sleep(webserv::http::response_fixed& response, webserv::http::http_handler* the_http_handler, webserv::pal::fs::easypipe& cgi_out); 
        };

    }
}

#endif
