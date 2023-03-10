#include "../../core/webservs.hpp"
#include "../../core/instance.hpp"

#include "http_handler.hpp"

namespace webserv {
    namespace http {

            /*
             *
             *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
             *
             */

            http_handler::http_handler(webserv::util::connection* new_connection, webserv::core::instance& instance)
                : basic_handler(new_connection), _instance(instance) {

            }

            http_handler::~http_handler() {
                
            }

            webserv::core::instance& http_handler::get_instance() { return _instance; }


            /*
             *
             *     S t a t e   M a c h i n e   F u n c t i o n s
             *
             */

            void http_handler::start() {
                // Written in inverse order due to stack
                later(&basic_handler::has_more);
                later(&http_handler::process_request);
                later(&http_handler::read_request);
            }

            void http_handler::restart() {
                // Written in inverse order due to stack
                later(&basic_handler::has_more);
                later(&http_handler::process_request);
                later(&http_handler::read_request);
            }

            void http_handler::read_request() {
                _the_request = request();

                later(&http_handler::read_body);
                later(&basic_handler::read_fields);
            }
                
                    void http_handler::parse_fields() {
                        webserv::util::stringflow  flow(_read_until_rnrn__buffer.to_string());
                        request_parser             parser(flow);

                        try {
                            parse_http_request_core(parser, _the_request);
                        } catch (webserv::util::parse_exception& e) {
                            _the_request.get_line().get_method() = webserv::http::http_method__invalid;
                        }
                    }

                void http_handler::read_body() {
                    if (_is_chunked_body()) {
                        later(&http_handler::read_body__from_chunked_body);
                        later(&basic_handler::read_chunked_body);
                    } else if (basic_handler::_is_normal_body()) {
                        _read_normal_body__expected_size = get_normal_body_size();
                        later(&http_handler::read_body__from_normal_body);
                        later(&basic_handler::read_normal_body);
                    } else {
                        // No body, do nothing
                        _the_request.get_body().clear();
                        return;
                    }
                }

                    void http_handler::read_body__from_normal_body() {
                        _the_request.get_body().assign(_read_normal_body__result);
                    }

                    void http_handler::read_body__from_chunked_body() {
                        _the_request.get_body().assign(_read_chunked_body__result);
                    }

                        void http_handler::read_chunked_body__parse_hex() {
                            if (basic_handler::parse_hex()) {
                                // Do nothing!
                            } else {
                                later(&http_handler::display_error_page_and_done);
                            }
                        }

                    void http_handler::parse_body() {
                        // Do nothing (for now)
                    }

            void http_handler::process_request() {
                webserv::core::instance* i = &get_instance();
                if (_the_request.get_fields().has("Host")) {
                    webserv::core::instance* ii = get_instance().get_webservs().get_instance_by_name(_the_request.get_fields().get_or_default("Host", ""));
                    if (ii != nullptr)
                        i = ii;
                }
                webserv::core::routing routing(*i, *this, _the_request);
                routing.look_up();
            }

            enum basic_handler::abort_mode http_handler::abort() {
                return abort_mode_continue;
            }


            void http_handler::has_more() {
                if (_is_keep_alive()) {
                    restart();
                } else {
                    later(&basic_handler::done);
                }
            }

            void http_handler::display_error_page_and_done() {
                webserv::core::routing routing(get_instance(), *this, _the_request);
                routing.error_and_flush(400);
                later(&basic_handler::done);
            }



            /*
             *
             *     U t i l i t i e s
             *
             */

            bool http_handler::_is_keep_alive() { return _the_request.get_fields().get_or_default("Connection", "") == "keep-alive"; }

            bool http_handler::_is_chunked_body() { return _the_request.get_fields().get_or_default("Transfer-Encoding", "") == "chunked"; }

            unsigned int http_handler::get_normal_body_size() {
                int v = _the_request.get_fields().get_int_or_default("Content-Length", 0);
                if (v < 0) return 0;
                return (unsigned int) v;
            }

    }
}
