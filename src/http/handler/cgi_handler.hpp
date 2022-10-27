#ifndef WEBSERV_HTTP_HANDLER_CGI_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_CGI_HANDLER_HPP

#include "../../defs.hpp"

#include "basic_handler.hpp"
#include "http_handler.hpp"

#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class cgi_handler : public basic_handler {
            webserv::http::http_handler* _http_handler;
            webserv::http::fields        _fields;

        public:
            /*
             *
             *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
             *
             */

            cgi_handler(webserv::util::connection* new_connection)
                : basic_handler(new_connection), _http_handler(NULL) {

            }

            ~cgi_handler() {
                if (_http_handler != NULL) {
                    _http_handler->wake_up();
                    _http_handler->decrement_refcount();
                }
            }

            void set_http_handler(webserv::http::http_handler* http_handler) {
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

            void start() {
                later(&cgi_handler::process_request);
                later(&cgi_handler::read_child_output);
            }

            void read_child_output() {
                later(&cgi_handler::read_body);
                later(&basic_handler::read_fields);
            }

                void parse_fields() {
                    webserv::util::stringflow   flow(_read_until_rnrn__buffer);
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

                void read_body() {  // TODO: Move to basic handler
                    if (basic_handler::_is_normal_body()) {
                        _read_normal_body__expected_size = get_normal_body_size();
                        later(&cgi_handler::read_body__from_normal_body);
                        later(&basic_handler::read_normal_body);
                    } else if (_is_chunked_body()) {
                        later(&cgi_handler::pipe_body);
                    } else {
                        // No body, do nothing
                        _body = "";
                        return;
                    }
                }

                    void read_body__from_normal_body() {
                        _body = _read_normal_body__result;
                    }

                    void read_body__from_chunked_body() {
                        _body = _read_chunked_body__result;
                        _fields.put("Content-Length", _body.size());
                        _fields.remove("Transfer-Encoding");
                    }

                        void read_chunked_body__parse_hex() {
                            unsigned int hex;

                            if (webserv::pal::cpp::hex_string_to_uint(_read_until_rn__buffer, hex)) {
                                if (hex == 0) {
                                    return;
                                } else {
                                    _read_normal_body__expected_size = hex;
                                    later(&basic_handler::read_chunked_body__continue);
                                    later(&basic_handler::read_until_rn);
                                    later(&basic_handler::read_normal_body);
                                }
                            } else
                                later(&basic_handler::total_failure);
                        }
                
                void pipe_body() {
                    if (_http_handler != NULL) {
                        std::ostream& out = _http_handler->out();
                        out << "HTTP/1.1 " << _fields.get_or_default("Status", "500 Internal Server Error") << "\r\n";
                        out << _fields;
                        out << "\r\n";
                        later(&cgi_handler::pipe_body__restart);
                    }   
                }

                    void pipe_body__restart() {
                        later(&cgi_handler::pipe_body__continue);
                        later(&basic_handler::read_next_char);
                    }

                    void pipe_body__continue() {
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

            void process_request() {
                if (_http_handler != NULL) {
                    std::ostream& out = _http_handler->out();
                    out << "HTTP/1.1 " << _fields.get_or_default("Status", "500 Internal Server Error") << "\r\n";
                    out << _fields;
                    out << "\r\n";
                    out << _body;
                }

                later(&cgi_handler::end_request);
            }

                void end_request() {
                   basic_handler::get_connection()->close();

                   stop();
                }

            enum basic_handler::abort_mode abort() {
                return abort_mode_terminate;
            }



            /*
             *
             *     U t i l i t i e s
             *
             */

            bool _is_chunked_body() { return _fields.get_or_default("Transfer-Encoding", "") == "chunked"; }

            unsigned int get_normal_body_size() {
                return (unsigned int) _fields.get_int_or_default("Content-Length", 0);
            }
        };

    }
}

#endif
