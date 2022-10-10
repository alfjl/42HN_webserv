#ifndef WEBSERV_CORE_CGI_CGI_MSG_HPP
#define WEBSERV_CORE_CGI_CGI_MSG_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace core {

        class cgi_message {
            std::string     _message_body;
        
        public:
            cgi_message(const std::string& message);
            ~cgi_message();

            void write_on(std::ostream& o);
        };

    }
}

#endif