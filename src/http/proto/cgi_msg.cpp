#include "../../core/webservs.hpp"
#include "../../pal/fork/fork.hpp"

#include "cgi_msg.hpp"

namespace webserv {
    namespace http {

        cgi_message::cgi_message(webserv::http::request& request, webserv::core::instance& current_instance, std::string path_translated)
         : _path_translated(path_translated), _request(request) ,_current_instance(current_instance) {
            _message_body.assign(request.get_body());

            switch (request.get_line().get_method()) {
                case webserv::http::http_method_head:   { _method = std::string("HEAD");   break; }
                case webserv::http::http_method_get:    { _method = std::string("GET");    break; }
                case webserv::http::http_method_put:    { _method = std::string("PUT");    break; }
                case webserv::http::http_method_post:   { _method = std::string("POST");   break; }
                case webserv::http::http_method_delete: { _method = std::string("DELETE"); break; }
                default:                                { _method = std::string("");       break; }
            }

            for (fields::const_iterator it = request.get_fields().begin(); it != request.get_fields().end(); ++it) {
                get_fields().put("HTTP_" + it->first, it->second);
            }

            setup_fields();
        }

        cgi_message::~cgi_message() {

        }

        fields& cgi_message::get_fields() { return _fields; }

        webserv::core::instance& cgi_message::get_current_instance() { return _current_instance; }

        const webserv::util::binary_buffer& cgi_message::get_message_body() { return _message_body; }


        void cgi_message::setup_fields() {
            // _fields.put("AUTH_TYPE", "");
            _fields.put("CONTENT_LENGTH", (int) _message_body.size());
            _fields.put("CONTENT_TYPE", _request.get_fields().get_or_default("Content-Type", "plain"));
            _fields.put("GATEWAY_INTERFACE", "CGI/1.1");
            _fields.put("PATH_INFO", _request.get_line().get_uri().get_path().to_absolute_string());
            _fields.put("PATH_TRANSLATED", _path_translated);
            _fields.put("REMOTE_ADDR", _request.get_conn().get_address_s());
            _fields.put("REMOTE_PORT", _request.get_conn().get_port());
            _fields.put("REQUEST_METHOD", _method);
            _fields.put("SERVER_NAME", get_current_instance().get_server_name());
            _fields.put("SERVER_PORT", get_current_instance().get_server_port()); 
            _fields.put("SERVER_PROTOCOL", "HTTP/1.1"); 
            _fields.put("SERVER_SOFTWARE", "Webserv/0.1");
        }

        void cgi_message::put_fields_into_task(webserv::pal::fork::fork_task& task) {
            for (fields::const_iterator it = _fields.begin(); it != _fields.end(); ++it) {
                task.add_env(it->first + "=" + it->second);
            }
        }

    }
}
