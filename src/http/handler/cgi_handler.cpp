#include "cgi_handler.hpp"

#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"

namespace webserv {
    namespace http {

            /*
             *
             *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
             *
             */

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
                if (_http_handler != NULL)
                    _http_handler->decrement_refcount();
                _http_handler = http_handler;
                if (_http_handler != NULL)
                    _http_handler->increment_refcount();
            }



           /*
             *
             *     S t a t e   M a c h i n e   F u n c t i o n s
             *
             */

            void cgi_handler::start() {
                later(&cgi_handler::process_request);
                later(&cgi_handler::read_child_output);
            }

            void cgi_handler::read_child_output() {
                later(&cgi_handler::read_body);
                later(&basic_handler::read_fields);
            }

                void cgi_handler::parse_fields() {
                    webserv::util::stringflow   flow(_read_until_rnrn__buffer.to_string());
                    request_parser              parser(flow);
                    _fields = webserv::http::fields();

                    bool correct = false;

                    try {
                        parse_request_fields(parser, _fields);
                        correct = true;
                    } catch (webserv::util::parse_exception& e) {

                    }

                    if (!correct)
                        later(&basic_handler::total_failure);
                }

                void cgi_handler::read_body() {
                    if (_is_chunked_body()) {
                        later(&cgi_handler::pipe_body);
                    } else if (basic_handler::_is_normal_body()) {
                        _read_normal_body__expected_size = get_normal_body_size();
                        later(&cgi_handler::read_body__from_normal_body);
                        later(&basic_handler::read_normal_body);
                    } else {
                        // No content size was given
                        _body.clear();
                        later(&cgi_handler::cat);  // Just write everything from the CGI to standard output
                    }
                }

                    void cgi_handler::read_body__from_normal_body() {
                        _body = _read_normal_body__result;
                    }

                    void cgi_handler::read_body__from_chunked_body() {
                        _body = _read_chunked_body__result;
                        _fields.put("Content-Length", _body.size());
                        _fields.remove("Transfer-Encoding");
                    }

                        void cgi_handler::read_chunked_body__parse_hex() {
                            if (basic_handler::parse_hex()) {
                                // Do nothing!
                            } else
                                later(&basic_handler::total_failure);
                        }
                
                void cgi_handler::pipe_body() {
                    if (_http_handler != NULL) {
                        std::ostream& out = _http_handler->out();
                        out << "HTTP/1.1 " << _fields.get_or_default("Status", "500 Internal Server Error") << "\r\n";
                        out << _fields;
                        out << "\r\n";
                        later(&cgi_handler::pipe_body__restart);
                    }
                }

                    void cgi_handler::pipe_body__restart() {
                        later(&cgi_handler::pipe_body__continue);
                        later(&basic_handler::read_next_char);
                    }

                    void cgi_handler::pipe_body__continue() {
                        if (_last_char.enabled()) {
                            if (_http_handler != NULL) {
                                std::ostream& out = _http_handler->out();
                                out << _last_char.value();
                            }
                            later(&cgi_handler::pipe_body__restart);
                        } else {
                            later(&cgi_handler::end_request);
                        }
                    }

            void cgi_handler::process_request() {
                if (_http_handler != NULL) {
                    std::ostream& out = _http_handler->out();
                    out << "HTTP/1.1 " << _fields.get_or_default("Status", "500 Internal Server Error") << "\r\n";
                    if (!_fields.has("Content-Length"))
                        _fields.put("Content-Length", _body.size());
                    out << _fields;
                    out << "\r\n";
                    _body.write_to_stream(out);
                }

                later(&cgi_handler::end_request);
            }

                void cgi_handler::end_request() {
                   basic_handler::get_connection()->close();

                   stop();
                }

            enum basic_handler::abort_mode cgi_handler::abort() {
                return abort_mode_terminate;
            }

            void cgi_handler::cat() {
                later(&cgi_handler::cat__restart);
            }

            void cgi_handler::cat__restart() {
                later(&cgi_handler::cat__continue);
                later(&basic_handler::read_next_char);
            }

            void cgi_handler::cat__continue() {
                if (_last_char.enabled()) {
                    _body.push(_last_char.value());
                    later(&cgi_handler::cat__restart);
                } else {
                    return;
                }
            }



            /*
             *
             *     U t i l i t i e s
             *
             */

            bool cgi_handler::_is_chunked_body() { return _fields.get_or_default("Transfer-Encoding", "") == "chunked"; }

            unsigned int cgi_handler::get_normal_body_size() {
                int v = _fields.get_int_or_default("Content-Length", 0);
                if (v < 0) return 0;
                return (unsigned int) v;
            }

    }
}
