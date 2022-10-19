#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/response.hpp"
#include "../../http/request.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"

#include "routing_table.hpp"

namespace webserv {
    namespace http { class http_handler; }
    
    namespace core {

        class   selector;

        class routing : public component {
            webserv::core::routing_table table;

        public:
            routing(instance& the_inst);
            ~routing();

            webserv::http::response_fixed* look_up(webserv::http::request_core& request, webserv::http::http_handler* the_http_handler);

            void handle_http_head(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route);
            void handle_http_get(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route);
            void handle_http_post(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route);
            void handle_http_delete(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route);

            void handle_cgi(webserv::http::response_fixed* response, webserv::http::request_core& request, route* route, webserv::http::http_handler* the_http_handler);

            void tick();

        protected:
            void head_start(std::ostringstream& ost, std::string s);
            void header_one(std::ostringstream& ost, std::string s);
            void header_three(std::ostringstream& ost, std::string s);
            void blockquote(std::ostringstream& ost, std::pair<std::string, std::string> quote);
            void set_delete_response(webserv::http::response_fixed& response);
            std::string itos(unsigned int code);
            void directory_listing(webserv::http::response_fixed& response, std::vector<webserv::util::path> paths);
            void file_listing(webserv::http::response_fixed& response, webserv::util::path file_path, std::ifstream* stream);
 
            void error_code(webserv::http::response_fixed& response, unsigned int code);
            void permanent_redirect_301(webserv::http::response_fixed& response, webserv::util::path path);
            void temporary_redirect_302(webserv::http::response_fixed& response, webserv::util::path path);
            void bad_request_400(webserv::http::response_fixed& response);
            void unauthorized_401(webserv::http::response_fixed& response);
            void not_found_404(webserv::http::response_fixed& response);
            void method_not_allowed_405(webserv::http::response_fixed& response);
            void gone_410(webserv::http::response_fixed& response);
            void teapot_418(webserv::http::response_fixed& response);
            void internal_server_error_500(webserv::http::response_fixed& response);
            void service_unavailable_503(webserv::http::response_fixed& response);

            std::string find_mime(std::string extension);
        };

    }
}

#endif
