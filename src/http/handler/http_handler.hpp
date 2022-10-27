#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "../../util/streamflow.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../parsing/request_parser.hpp"
#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class http_handler : public basic_handler {
            webserv::core::routing& _routing;
            request                 _the_request;

        public:
            /*
             *
             *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
             *
             */

            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing);

            ~http_handler();

            webserv::core::routing& get_routing();


            /*
             *
             *     S t a t e   M a c h i n e   F u n c t i o n s
             *
             */

            void start();

            void restart();

            void read_request();
                
                    void parse_fields();

                void read_body();

                    void read_body__from_normal_body();

                    void read_body__from_chunked_body();

                        void read_chunked_body__parse_hex();

                    void parse_body();

            void process_request();

            enum basic_handler::abort_mode abort();

            void has_more();

            /*
             *
             *     U t i l i t i e s
             *
             */

            bool _is_keep_alive();

            bool _is_chunked_body();

            unsigned int get_normal_body_size();
        };

    }
}

#endif
