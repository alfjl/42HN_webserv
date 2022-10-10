#ifndef WEBSERV_CORE_ROUTING_ROUTE_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_HPP

#include "../../defs.hpp"

#include "../../http/request.hpp"
#include "../../util/optional.hpp"

namespace webserv {
    namespace core {
        
        class route {
            webserv::util::path                                             _file_target;
            webserv::util::optional<std::set<webserv::http::http_method> >  _allowed_methods;

        public:
            route(webserv::util::path file_target);
            route(const route& other);
            virtual ~route();

            webserv::util::path get_file_target();

            bool is_method_allowed(webserv::http::http_method method);

            route* set_path(webserv::util::path file_target);
            route* set_allowed_method(webserv::http::http_method method);
            route* unset_allowed_method(webserv::http::http_method method);

            virtual bool is_cgi();
            virtual bool is_redirection();
            virtual bool is_error();
        };

        class file_route : public route {
        public:
            file_route(webserv::util::path file_target);
            file_route(const file_route& other);
        };

        class cgi_route : public route {
        public:
            cgi_route(webserv::util::path file_target);
            cgi_route(const cgi_route& other);

            bool is_cgi();
        };

        class redirection_route : public route {
        public:
            redirection_route(webserv::util::path file_target);
            redirection_route(const redirection_route& other);

            bool is_redirection();
        };

        class error_route : public route {
        public:
            error_route(webserv::util::path file_target);
            error_route(const error_route& other);

            bool is_error();
        };

    }
}

#endif
