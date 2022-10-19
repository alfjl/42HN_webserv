#include "cgi_handler.hpp"

#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"

namespace webserv {
    namespace http {

        cgi_handler::cgi_handler(webserv::util::connection* new_connection)
            : basic_handler(new_connection), _http_handler(NULL) {

        }

        cgi_handler::~cgi_handler() {
            if (_http_handler != NULL) {
                _http_handler->wake_up();
                _http_handler->decrement_refcount();
            }
        }

        void cgi_handler::set_http_handler(webserv::http::http_handler* http_handler) {
            // TODO: Throw exception if handler is already set
            _http_handler = http_handler;
            if (_http_handler != NULL)
                _http_handler->increment_refcount();
        }

        void cgi_handler::start() {
            next(&cgi_handler::wait_for_char);
            later(&cgi_handler::char_arrived);
        }

        enum basic_handler::abort_mode cgi_handler::abort() {
            return abort_mode_terminate;
        }

        void cgi_handler::char_arrived() {
            // std::cerr << "\033[35m" << basic_handler::get_last_char() << "\033[0m";
            // next(&cgi_handler::start);
            _buffer += basic_handler::get_last_char();
            if (_buffer.find("\r\n\r\n") != std::string::npos) {
                next(&cgi_handler::process_head);
            } else {
                next(&cgi_handler::start);
            }
        }

        void cgi_handler::process_head() {
            webserv::util::stringflow   flow(_buffer);
            request_parser  parser(flow);
            _fields = webserv::http::fields();

            bool correct = false;
            
            try {
                parse_request_fields(parser, _fields);
                correct = true;
            } catch (std::runtime_error& e) {   // TODO: webserv::util::parse_exception

            }

            _body = "";

            if (correct) {
                // if (_into.get_fields().get_or_default("Transfer-Encoding", "") == "chunked") {
                //     next(&basic_handler::parse_chunked_body);
                //     later(&cgi_handler::process_request);
                // } else if (_into.get_fields().has("Content-Length")) {
                //     int bytes;
                //     if (webserv::pal::cpp::string_to_int(_into.get_fields().get_or_default("Content-Length", "").c_str(), bytes)) {
                //         this->_bytes = bytes;
                //         next(&basic_handler::parse_normal_body);
                //         later(&cgi_handler::process_request);
                //     } else {
                //         next(&basic_handler::total_failure);
                //     }
                // } else {
                //     next(&cgi_handler::process_request);
                // }
                next(&cgi_handler::process_request);
            } else {
                std::cout << "Error in request!" << std::endl;
                next(&basic_handler::total_failure);
            }
        }

        void cgi_handler::process_request() {
            std::cout << "CGI processing request..." << std::endl;
            std::cout << _fields << std::endl;

            if (_http_handler != NULL) {
                std::ostream& out = _http_handler->out();
                out << "HTTP/1.1 " << _fields.get_or_default("Status", "500 Internal Server Error") << "\r\n";
                out << _fields; // TODO: Is this correct?
                out << "\r\n";
                //TODO: out << _body;
            }

            next(&cgi_handler::end_request);
        }

        void cgi_handler::end_request() {
            basic_handler::get_connection()->close();

            stop();
        }

    }
}
