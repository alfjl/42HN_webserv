#include "cgi_msg.hpp"

namespace webserv {
    namespace core {

    cgi_message::cgi_message(const std::string& message) : _message_body(message) {

    }

    cgi_message::~cgi_message() {

    }

    void cgi_message::write_on(std::ostream& o) {
        o << _message_body.c_str();
    }


    }
}