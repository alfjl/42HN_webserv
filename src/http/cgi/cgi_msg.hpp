#ifndef WEBSERV_HTTP_CGI_CGI_MSG_HPP
#define WEBSERV_HTTP_CGI_CGI_MSG_HPP

#include "../../defs.hpp"

#include "../cgi_headers.hpp"

namespace webserv {
    namespace http {

        class cgi_message {
            std::string                _message_body;
            webserv::http::cgi_headers _headers;
        
        public:
            cgi_message(std::string message);
            ~cgi_message();

            void write_on(std::ostream& o);
        };

    }
}

#endif