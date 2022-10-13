#include "cgi_msg.hpp"

#include "../../pal/fork/fork.hpp"

namespace webserv {
    namespace http {

        cgi_message::cgi_message(webserv::http::request_core& request) {
            _message_body = request.get_body();

            switch (request.get_line().get_method()) {
                case webserv::http::http_method_head:   { _method = std::string("HEAD");   break; }
                case webserv::http::http_method_get:    { _method = std::string("GET");    break; }
                case webserv::http::http_method_put:    { _method = std::string("PUT");    break; }
                case webserv::http::http_method_post:   { _method = std::string("POST");   break; }
                case webserv::http::http_method_delete: { _method = std::string("DELETE"); break; }
                default:                                { _method = std::string("");       break; }
            }
        }

        cgi_message::~cgi_message() {

        }

        void cgi_message::setup_fields() {
            _fields.put("AUTH_TYPE", "");
            _fields.put("CONTENT_LENGTH", (int) _message_body.size());
            _fields.put("CONTENT_TYPE", _fields.get_or_default("CONTENT_TYPE", "plain"));
            _fields.put("GATEWAY_INTERFACE", "CGI/1.1");
            _fields.put("PATH_INFO", "");  // TODO
            _fields.put("PATH_TRANSLATED", ""); // TODO
            _fields.put("QUERY_STRING", "");  // TODO
            _fields.put("REMOTE_ADDR", "127.0.0.1");  // TODO: localhost
            _fields.put("REMOTE_HOST", "");
            _fields.put("REMOTE_IDENT", ""); // Not really needed
            _fields.put("REMOTE_USER", "");
            _fields.put("REQUEST_METHOD", _method);
            _fields.put("SCRIPT_NAME", "");
            _fields.put("SERVER_NAME", ""); // = HOST cut until :
            _fields.put("SERVER_PORT", ""); // = HOST: alles nach :
            _fields.put("SERVER_PROTOCOL", "");
            _fields.put("SERVER_SOFTWARE", "");
        }

        void cgi_message::write_on(std::ostream& o) {
            o << "CGI_TEST\r\n"; // TODO: Remove!
            o << _fields << "\r\n" << _message_body;
        }

    }
}
