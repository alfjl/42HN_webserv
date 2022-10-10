#ifndef WEBSERV_CORE_ROUTING_ROUTE_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_HPP

#include "../../http/request.hpp"

namespace webserv {
    namespace core {
        
        class route {
            webserv::util::path     _file_target;

        public:
            route(webserv::util::path file_target);
            route(const route& other);
            virtual ~route();

            webserv::util::path get_file_target();

            bool is_method_allowed(webserv::http::http_method method);
            virtual bool is_cgi();
        };

        class file_route : route {
        public:
            file_route(webserv::util::path file_target);
            file_route(const file_route& other);
        };

        class redirection_route : route {
        public:
            redirection_route(webserv::util::path file_target);
            redirection_route(const redirection_route& other);
        };

        class error_route : route {
        public:
            error_route(webserv::util::path file_target);
            error_route(const error_route& other);
        };
    }
}

#endif
