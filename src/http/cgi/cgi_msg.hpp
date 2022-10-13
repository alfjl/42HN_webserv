#ifndef WEBSERV_HTTP_CGI_CGI_MSG_HPP
#define WEBSERV_HTTP_CGI_CGI_MSG_HPP

#include "../../defs.hpp"

#include "../fields.hpp"
#include "../request.hpp"

namespace webserv {
    namespace http {

        class cgi_message {
            std::string                  _method;
            std::string                  _message_body;
            webserv::http::fields        _fields;
            webserv::http::request_core& _request;

        public:
            cgi_message(webserv::http::request_core& request);
            ~cgi_message();

            fields& get_fields();

            void setup_fields();

            void write_on(std::ostream& o);
        };

    }
}

#endif