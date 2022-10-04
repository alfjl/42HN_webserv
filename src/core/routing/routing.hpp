#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/response.hpp"
#include "../../http/request.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"

namespace webserv {
    namespace core {

        class   selector;

        class routing : public component {
        public:
            routing(instance& the_inst);
            ~routing();

            webserv::http::response_fixed* look_up(webserv::http::request_core& request);
            webserv::http::response_fixed* http_get_method(webserv::http::response_fixed *response, webserv::http::request_core& request);

            void tick();

        protected:
            void header_start(std::ostringstream* ost, std::string s);
            std::string itos(unsigned int code);
            void directory_listing(webserv::http::response_fixed* response, std::vector<webserv::util::path> paths);
            void file_listing(webserv::http::response_fixed* response, webserv::util::path file_path, std::ifstream* stream);
 
            void error_code(webserv::http::response_fixed* response, unsigned int code);
            void permanent_redirect_301(webserv::http::response_fixed* response);
            void temporary_redirect_302(webserv::http::response_fixed* response);
            void bad_request_400(webserv::http::response_fixed* response);
            void unauthorized_401(webserv::http::response_fixed* response);
            void not_found_404(webserv::http::response_fixed* response);
            void gone_410(webserv::http::response_fixed* response);
            void teapot_418(webserv::http::response_fixed* response);
            void internal_server_error_500(webserv::http::response_fixed* response);
            void service_unavailable_503(webserv::http::response_fixed* response);

            std::string find_mime(std::string extension);
        };

    }
}

#endif
