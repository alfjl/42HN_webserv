#include "cgi_msg.hpp"

#include "../../pal/fork/fork.hpp"

namespace webserv {
    namespace http {

        cgi_message::cgi_message(std::string message) : _message_body(message) {

        }

        cgi_message::~cgi_message() {

        }

        void cgi_message::write_on(std::ostream& o) {
            o << "CGI_TEST\r\n"; // TODO: Remove!
            o << _headers << "\r\n" << _message_body;
        }

    }
}

#include <map>