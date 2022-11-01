#ifndef WEBSERV_CORE_ROUTING_ROUTE_ROUTE_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_ROUTE_HPP

#include "../../../defs.hpp"

#include "route_meta.hpp"

#include "../../../http/proto/request.hpp"
#include "../../../pal/cpp/optional.hpp"

namespace webserv {
    namespace core {

        struct match_info {
            webserv::util::path wildcard_path;
        };

        class route {
            webserv::util::path  _file_target;
        
        protected:
            route_meta*          _meta;

        public:
            route(webserv::util::path file_target);
            route(webserv::util::path file_target, route_meta* meta);
            route(const route& other);
            virtual ~route();

            webserv::util::path get_file_target();

            bool is_method_allowed(webserv::http::http_method method);
            webserv::pal::cpp::optional<unsigned int> get_max_body();

            route* set_path(webserv::util::path file_target);

            route* disable_all_methods();
            route* set_allowed_method(webserv::http::http_method method);
            route* unset_allowed_method(webserv::http::http_method method);
            route* set_max_body(unsigned int max);
            route* set_index_page(webserv::util::path index);
            route* set_directory_listing(bool state);

            virtual bool is_cgi();
            virtual bool is_redirection();
            virtual bool is_permanent_redirection();
            virtual bool is_error(int& code);

            virtual route* build(match_info& meta) = 0;
        };

        class file_route : public route {
        public:
            file_route(webserv::util::path file_target);
            file_route(webserv::util::path file_target, route_meta* meta);
            file_route(const file_route& other);
            route* build(match_info& meta);
        };

        class cgi_route : public route {
        public:
            cgi_route(webserv::util::path file_target);
            cgi_route(webserv::util::path file_target, route_meta* meta);
            cgi_route(const cgi_route& other);

            bool is_cgi();
            route* build(match_info& meta);

            webserv::pal::cpp::optional<std::string> get_executor();
            cgi_route* set_executor(std::string executor);
        };

        class redirection_route : public route {
        public:
            redirection_route(webserv::util::path file_target);
            redirection_route(webserv::util::path file_target, route_meta* meta);
            redirection_route(const redirection_route& other);

            bool is_redirection();
            route* build(match_info& meta);
        };

        class permanent_redirection_route : public route {
        public:
            permanent_redirection_route(webserv::util::path file_target);
            permanent_redirection_route(webserv::util::path file_target, route_meta* meta);
            permanent_redirection_route(const permanent_redirection_route& other);

            bool is_permanent_redirection();
            route* build(match_info& meta);
        };

        class error_route : public route {
            int _code;

        public:
            error_route(int code);
            error_route(int code, route_meta* meta);
            error_route(const error_route& other);

            bool is_error(int& code);
            route* build(match_info& meta);
        };

        // class wildcard_route : public route {
        // public:
        //     wildcard_route(webserv::util::path file_target);
        //     wildcard_route(const wildcard_route& other);

        //     virtual route* build(match_info& meta);
        // };

    }
}

#endif
