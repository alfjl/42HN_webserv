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
            cgi_handler(webserv::util::connection* new_connection);
            ~cgi_handler();

            void set_http_handler(webserv::http::http_handler* http_handler);

                                      void start();
            enum basic_handler::abort_mode abort();

            void parse_body_util();

            void char_arrived();

            void process_head();
            void process_request();
            void end_request();
        };

    }
}

#endif
