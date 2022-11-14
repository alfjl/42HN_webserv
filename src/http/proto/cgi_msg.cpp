#include "../../core/webservs.hpp"
#include "../../pal/fork/fork.hpp"

#include "cgi_msg.hpp"

namespace webserv {
    namespace http {

        cgi_message::cgi_message(webserv::http::request& request, webserv::core::instance& current_instance, std::string path_translated)
         : _path_translated(path_translated), _request(request) ,_current_instance(current_instance) {
            _message_body = request.get_body().to_string(); // XXX!

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

        std::string cgi_message::get_message_body() { return _message_body; }


        void cgi_message::setup_fields() {
            // _fields.put("AUTH_TYPE", "");
            _fields.put("CONTENT_LENGTH", (int) _message_body.size());
            _fields.put("CONTENT_TYPE", _request.get_fields().get_or_default("Content-Type", "plain"));
            _fields.put("GATEWAY_INTERFACE", "CGI/1.1");
            _fields.put("PATH_INFO", _request.get_line().get_uri().get_path().to_absolute_string());
            _fields.put("PATH_TRANSLATED", _path_translated);
            _fields.put("QUERY_STRING", "");  // TODO: Needs to be parsed as well!
            _fields.put("REMOTE_ADDR", "127.0.0.1");  // TODO: localhost ?read out request field X-Forwarded-For?
            _fields.put("REMOTE_HOST", _request.get_fields().get_or_default("Host", "")); // Not really needed: "only if server performed such lookup"
            // _fields.put("REMOTE_IDENT", ""); // Not really needed: "only if server performed such lookup"
            // _fields.put("REMOTE_USER", "");
            _fields.put("REQUEST_METHOD", _method);
            _fields.put("SCRIPT_NAME", ""); // relative path to the program, like /cgi-bin/script.cgi. Or just leave empty?
            _fields.put("SERVER_NAME", ""); // = get_current_instance().get_server_name()
            _fields.put("SERVER_PORT", ""); // = get_current_instance().get_server_port()
            _fields.put("SERVER_PROTOCOL", "HTTP/1.1"); // 
            _fields.put("SERVER_SOFTWARE", "Webserv/0.1"); // change to final name of our webserver
        }

        // void cgi_message::write_on(std::ostream& o, int infd) {
        //     (void) infd;
        //     for (unsigned int i = 0; i < _message_body.size(); i++) {
        //         if (!get_current_instance().get_webservs().is_running()) {
        //             std::cout << "Oompah!" << std::endl;
        //         }

        //         if (i % 10000 == 0) {
        //             get_current_instance().get_driver().tick();
        //         }
        //         o << _message_body[i];
        //     }
        // }

        void cgi_message::put_fields_into_task(webserv::pal::fork::fork_task& task) {
            for (fields::const_iterator it = _fields.begin(); it != _fields.end(); ++it) {
                task.add_env(it->first + "=" + it->second);
            }
        }

    }
}
