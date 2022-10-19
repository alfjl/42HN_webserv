#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class http_handler : public basic_handler {
            webserv::core::routing& _routing;
            request_core            _into;

        public:
            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing);
            ~http_handler();

            void fall_asleep();
            void wake_up();

                                      void start();
            enum basic_handler::abort_mode abort();

            void char_arrived();

            void process_head();
            void process_request();
            void end_request();

            webserv::core::routing& get_routing();
        };

    }
}

#endif
