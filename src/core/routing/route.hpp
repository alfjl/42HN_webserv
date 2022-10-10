#ifndef WEBSERV_CORE_ROUTING_ROUTE_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_HPP

#include "../../http/request.hpp"

namespace webserv {
    namespace core {
        
        class route {
            webserv::util::path                  _file_target;
            //optional set

        public:
            route(webserv::util::path file_target);
            route(const route& other);

            webserv::util::path get_file_target();

            bool is_method_allowed(webserv::http::http_method method);
            bool is_cgi();

            void write_on(std::ostream& o);
        };

    }
}

#endif
