#include "cgi_msg.hpp"

#include "../../pal/fork/fork.hpp"

namespace webserv {
    namespace http {

        cgi_message::cgi_message(std::string message) : _message_body(message) {

        }

        cgi_message::~cgi_message() {

        }

        void cgi_message::setup_fields() {
            _fields.put("AUTH_TYPE", "");
            _fields.put("CONTENT_LENGTH", (int) _message_body.size());
            _fields.put("CONTENT_TYPE", "plain"); // TODO
            _fields.put("GATEWAY_INTERFACE", "CGI/1.1");
            _fields.put("PATH_INFO", "");  // TODO
            _fields.put("PATH_TRANSLATED", ""); // TODO
            _fields.put("QUERY_STRING", "");  // TODO
            _fields.put("REMOTE_ADDR", "127.0.0.1");  // TODO: localhost
            _fields.put("REMOTE_HOST", "");
            _fields.put("REMOTE_IDENT", ""); // Not really needed
            _fields.put("REMOTE_USER", "");
            _fields.put("REQUEST_METHOD", "");
            _fields.put("SCRIPT_NAME", "");
            _fields.put("SERVER_NAME", "");
            _fields.put("SERVER_PORT", "");
            _fields.put("SERVER_PROTOCOL", "");
            _fields.put("SERVER_SOFTWARE", "");
        }

        void cgi_message::write_on(std::ostream& o) {
            o << "CGI_TEST\r\n"; // TODO: Remove!
            o << _fields << "\r\n" << _message_body;
        }

    }
}
