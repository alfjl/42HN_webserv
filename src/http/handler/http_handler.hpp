#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class http_handler : public basic_handler {
            webserv::core::routing& _routing;

        public:
            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing);
            ~http_handler();

            void fall_asleep();
            void wake_up();

            void start();
            void abort();

            void char_arrived();

            void process_head();
            void process_request();
            void end_request();
        };

    }
}

#endif
