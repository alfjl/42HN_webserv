#ifndef WEBSERV_CORE_ROUTING_ROUTE_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_HPP

#include "../../defs.hpp"

#include "../../http/proto/request.hpp"
#include "../../pal/cpp/optional.hpp"

namespace webserv {
    namespace core {

        struct route_meta {
            webserv::util::path wildcard_path;
        };

        class route {
            webserv::util::path                                             _file_target;
        
        protected:
            webserv::pal::cpp::optional<std::set<webserv::http::http_method> >  _allowed_methods;

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
            virtual bool is_permanent_redirection();
            virtual bool is_error(int& code);

            virtual route* build(route_meta& meta) { return this; }
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

        class permanent_redirection_route : public route {
        public:
            permanent_redirection_route(webserv::util::path file_target);
            permanent_redirection_route(const permanent_redirection_route& other);

            bool is_permanent_redirection();
        };

        class error_route : public route {
            int _code;

        public:
            error_route(int code);
            error_route(const error_route& other);

            bool is_error(int& code);
        };

        class wildcard_route : public route {
        public:
            wildcard_route(webserv::util::path file_target);
            wildcard_route(const wildcard_route& other);

            virtual route* build(route_meta& meta);
        };

    }
}

#endif
