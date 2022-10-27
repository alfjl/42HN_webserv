#ifndef WEBSERV_HTTP_HANDLER_CGI_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_CGI_HANDLER_HPP

#include "../../defs.hpp"

#include "basic_handler.hpp"
#include "http_handler.hpp"

#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class cgi_handler : public basic_handler {
            webserv::http::http_handler* _http_handler;
            webserv::http::fields        _fields;

        public:
            /*
             *
             *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
             *
             */

            cgi_handler(webserv::util::connection* new_connection);

            ~cgi_handler();

            void set_http_handler(webserv::http::http_handler* http_handler);



           /*
             *
             *     S t a t e   M a c h i n e   F u n c t i o n s
             *
             */

            void start();

            void read_child_output();

                void parse_fields();

                void read_body();

                    void read_body__from_normal_body();

                    void read_body__from_chunked_body();

                        void read_chunked_body__parse_hex();
                
                void pipe_body();

                    void pipe_body__restart();

                    void pipe_body__continue();

            void process_request();

                void end_request();

            enum basic_handler::abort_mode abort();



            /*
             *
             *     U t i l i t i e s
             *
             */

            bool _is_chunked_body();

            unsigned int get_normal_body_size();
        };

    }
}

#endif
