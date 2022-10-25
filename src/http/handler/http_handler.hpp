#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class http_handler : public basic_handler {
            webserv::core::routing& _routing;
            request                 _into;

        public:
            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing);
            ~http_handler();

                                      void start();
            enum basic_handler::abort_mode abort();

            void char_arrived();

            void process_head();
            void process_request();
            void end_request();
            void parse_body_util();

            webserv::core::routing& get_routing();
            request& get_into();
        };

    }
}

#endif
