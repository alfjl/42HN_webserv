#include "route.hpp"

namespace webserv {
    namespace core {

        route::route(webserv::util::path file_target) : _file_target(file_target) {

        }

        webserv::util::path route::get_file_target() { return _file_target; }

        bool route::is_method_allowed(webserv::http::http_method method) {
            /*
             * TODO!
             */
            return true;
        }

    }
}
