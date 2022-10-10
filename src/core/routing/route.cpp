#include "route.hpp"

namespace webserv {
    namespace core {

        route::route(webserv::util::path file_target) : _file_target(file_target) {

        }

        route::route(const route& other) {
            if (this != &other)
                _file_target = other._file_target;
        }

        route::~route() {

        }

        webserv::util::path route::get_file_target() { return _file_target; }

        bool route::is_method_allowed(webserv::http::http_method method) {
            /*
             * TODO!
             */
            return true;
        }

        bool route::is_cgi(){
            /*
                TODO!
            */
            
            return false;
        }


        file_route::file_route(webserv::util::path file_target) : route(file_target) {

        }

        file_route::file_route(const file_route& other) : route(other) {

        }


        redirection_route::redirection_route(webserv::util::path file_target) : route(file_target) {

        }

        redirection_route::redirection_route(const redirection_route& other) : route(other) {

        }


        error_route::error_route(webserv::util::path file_target) : route(file_target) {

        }

        error_route::error_route(const error_route& other) : route(other) {

        }
        
    }
}
