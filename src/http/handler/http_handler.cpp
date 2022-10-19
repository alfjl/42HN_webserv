#include "http_handler.hpp"

#include "../../core/routing/routing.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"
#include "../response.hpp"

namespace webserv {
    namespace http {

        http_handler::http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing)
            : basic_handler(new_connection), _routing(routing) {
                
        }

        http_handler::~http_handler() {

        }

        void http_handler::fall_asleep() {
            // TODO: Implement!
        }     

        void http_handler::wake_up() {
            // TODO: Implement!
        }

        void http_handler::start() {
            next(&basic_handler::wait_for_char);
            later(&http_handler::char_arrived);
        }

        enum basic_handler::abort_mode http_handler::abort() {
            return abort_mode_terminate;
        }

        void http_handler::char_arrived() {
            _buffer += basic_handler::get_last_char();
            if (_buffer.find("\r\n\r\n") != std::string::npos) {
                next(&http_handler::process_head);
            } else {
                next(&http_handler::start);
            }
        }

        void http_handler::process_head() {
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
                    later(&http_handler::process_request);
                } else if (_into.get_fields().has("Content-Length")) {
                    int bytes;
                    if (webserv::pal::cpp::string_to_int(_into.get_fields().get_or_default("Content-Length", "").c_str(), bytes)) {
                        this->_bytes = bytes;
                        next(&basic_handler::parse_normal_body);
                        later(&http_handler::process_request);
                    } else {
                        next(&basic_handler::total_failure);
                    }
                } else {
                    next(&http_handler::process_request);
                }
            } else {
                std::cout << "Error in request!" << std::endl;
                next(&basic_handler::total_failure);
            }
        }

        void http_handler::process_request() {
            _into.get_body() = _body;
            _body = "";

            std::cout << "Serving " << _into.get_line().get_uri().get_path().to_absolute_string() << "... ";
            std::flush(std::cout);

            response* response = _routing.look_up(_into, this);

            std::cout << response->get_code() << std::endl;

            response->write(*basic_handler::get_connection());

            response->decrement_refcount();

            next(&http_handler::end_request);
        }

        void http_handler::end_request() {
            basic_handler::get_connection()->close();

            stop();
        }

        webserv::core::routing& http_handler::get_routing() { return _routing; }


    }
}
