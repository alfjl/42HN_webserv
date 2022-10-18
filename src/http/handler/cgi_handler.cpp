#include "cgi_handler.hpp"

#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"

namespace webserv {
    namespace http {

        cgi_handler::cgi_handler(webserv::util::connection* new_connection, webserv::http::http_handler* http_handler)
            : basic_handler(new_connection), _http_handler(http_handler) {
                _http_handler->fall_asleep(); // This should happen somewhere else
        }

        cgi_handler::~cgi_handler() {
            _http_handler->wake_up();
        }

        void cgi_handler::start() {
            next(&cgi_handler::wait_for_char);
            later(&cgi_handler::char_arrived);
        }

        void cgi_handler::abort() {
            // TODO
        }

        void cgi_handler::char_arrived() {
            // std::cerr << "\033[35m" << basic_handler::get_last_char() << "\033[0m";
            // next(&cgi_handler::start);
            _buffer += basic_handler::get_last_char();
            if (_buffer.find("\r\n\r\n") != std::string::npos) {
                next(&http_handler::process_head);
            } else {
                next(&http_handler::start);
            }
        }

        void cgi_handler::process_head() {
            webserv::util::stringflow   flow(_buffer);
            request_parser  parser(flow);
            _into = request_core();

            bool correct = false;
            
            try {
                parse_http_request_core(parser, _into);
                correct = true;
            } catch (std::runtime_error& e) {   // TODO: webserv::util::parse_exception

            }

            _body = "";

            if (correct) {
                if (_into.get_fields().get_or_default("Transfer-Encoding", "") == "chunked") {
                    next(&basic_handler::parse_chunked_body);
                    later(&cgi_handler::process_request);
                } else if (_into.get_fields().has("Content-Length")) {
                    int bytes;
                    if (webserv::pal::cpp::string_to_int(_into.get_fields().get_or_default("Content-Length", "").c_str(), bytes)) {
                        this->_bytes = bytes;
                        next(&basic_handler::parse_normal_body);
                        later(&cgi_handler::process_request);
                    } else {
                        next(&basic_handler::total_failure);
                    }
                } else {
                    next(&cgi_handler::process_request);
                }
            } else {
                std::cout << "Error in request!" << std::endl;
                next(&basic_handler::total_failure);
            }
        }

        void cgi_handler::process_request() {
            _into.get_body() = _body;
            _body = "";

            std::cout << "CGI Serving " << _into.get_line().get_uri().get_path().to_absolute_string() << "... ";
            std::flush(std::cout);

            response* response = _http_handler->get_routing().look_up(_into);

            std::cout << response->get_code() << std::endl;

            response->write(*basic_handler::get_connection());

            next(&cgi_handler::end_request);
        }

        void cgi_handler::end_request() {
            basic_handler::get_connection()->close();

            stop();
        }

    }
}
