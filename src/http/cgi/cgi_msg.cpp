#include "cgi_msg.hpp"

#include "../../pal/fork/fork.hpp"

namespace webserv {
    namespace http {

        cgi_message::cgi_message(webserv::http::request_core& request, webserv::core::instance& current_instance)
         : _request(request), _current_instance(current_instance) {
            _message_body = request.get_body();

            switch (request.get_line().get_method()) {
                case webserv::http::http_method_head:   { _method = std::string("HEAD");   break; }
                case webserv::http::http_method_get:    { _method = std::string("GET");    break; }
                case webserv::http::http_method_put:    { _method = std::string("PUT");    break; }
                case webserv::http::http_method_post:   { _method = std::string("POST");   break; }
                case webserv::http::http_method_delete: { _method = std::string("DELETE"); break; }
                default:                                { _method = std::string("");       break; }
            }

            setup_fields();
        }

        cgi_message::~cgi_message() {

        }

        fields& cgi_message::get_fields() { return _fields; }

        webserv::core::instance& cgi_message::get_current_instance() { return _current_instance; }

        void cgi_message::setup_fields() {
            _fields.put("AUTH_TYPE", "");
            _fields.put("CONTENT_LENGTH", (int) _message_body.size());
            _fields.put("CONTENT_TYPE", _request.get_fields().get_or_default("Content-Type", "plain"));
            _fields.put("GATEWAY_INTERFACE", "CGI/1.1");
            _fields.put("PATH_INFO", _request.get_line().get_uri().get_path().to_absolute_string());
            _fields.put("PATH_TRANSLATED", ""); // TODO
            _fields.put("QUERY_STRING", "");  // TODO
            _fields.put("REMOTE_ADDR", "127.0.0.1");  // TODO: localhost
            _fields.put("REMOTE_HOST", "");
            _fields.put("REMOTE_IDENT", ""); // Not really needed
            _fields.put("REMOTE_USER", "");
            _fields.put("REQUEST_METHOD", _method);
            _fields.put("SCRIPT_NAME", "");
            _fields.put("SERVER_NAME", ""); // = get_current_instance().get_server_name()
            _fields.put("SERVER_PORT", ""); // = get_current_instance().get_server_port()
            _fields.put("SERVER_PROTOCOL", "HTTP/1.1"); // 
            _fields.put("SERVER_SOFTWARE", "Webserv/0.1"); // name of our webserver
        }

        void cgi_message::write_on(std::ostream& o) {
            o << _message_body;
        }

    }
}
