#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "../../util/streamflow.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../parsing/request_parser.hpp"
#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class http_handler : public basic_handler {
            webserv::core::routing& _routing;
            request                 _the_request;

        public:
            /*
             *
             *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
             *
             */

            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing)
                : basic_handler(new_connection), _routing(routing) {

            }

            ~http_handler() {
                
            }

            webserv::core::routing& get_routing() { return _routing; }


            /*
             *
             *     S t a t e   M a c h i n e   F u n c t i o n s
             *
             */

            void start() {
                // Written in inverse order due to stack
                later(&basic_handler::has_more);
                later(&http_handler::process_request);
                later(&http_handler::read_request);
            }

            void read_request() {
                _the_request = request();

                later(&http_handler::read_body);
                later(&http_handler::read_fields);
            }
                
                    void parse_fields() {
                        webserv::util::stringflow  flow(_read_until_rnrn__buffer);
                        request_parser             parser(flow);

                        bool correct = false;
                        
                        try {
                            parse_http_request_core(parser, _the_request);
                            correct = true;
                        } catch (webserv::util::parse_exception& e) {

                        }

                        if (!correct)
                            later(&basic_handler::parse_error);
                    }

                void read_body() {  // TODO: Move to basic handler
                    if (basic_handler::_is_normal_body()) {
                        _read_normal_body__expected_size = get_normal_body_size();
                        later(&http_handler::read_body__from_normal_body);
                        later(&http_handler::read_normal_body);
                    } else if (_is_chunked_body()) {
                        later(&http_handler::read_body__from_chunked_body);
                        later(&http_handler::read_chunked_body);
                    } else {
                        // No body, do nothing
                        _the_request.get_body() = "";
                        return;
                    }
                }

                    void read_body__from_normal_body() {
                        _the_request.get_body() = _read_normal_body__result;
                    }

                    void read_body__from_chunked_body() {
                        _the_request.get_body() = _read_chunked_body__result;
                    }

                        void read_chunked_body__parse_hex() {
                            unsigned int hex;

                            if (webserv::pal::cpp::hex_string_to_uint(_read_until_rn__buffer, hex)) {
                                if (hex == 0) {
                                    return;
                                } else {
                                    _read_normal_body__expected_size = hex;
                                    later(&http_handler::read_chunked_body__continue);
                                    later(&basic_handler::read_until_rn);
                                    later(&http_handler::read_normal_body);
                                }
                            } else
                                later(&basic_handler::parse_error);
                        }

                    void parse_body() {
                        // Do nothing (for now)
                    }

            void process_request() {
                _routing.look_up(_the_request, this);
            }

            enum basic_handler::abort_mode abort() {
                return abort_mode_continue;
            }

            /*
             *
             *     U t i l i t i e s
             *
             */

            bool _is_chunked_body() { return _the_request.get_fields().get_or_default("Transfer-Encoding", "") == "chunked"; }

            unsigned int get_normal_body_size() {
                return (unsigned int) _the_request.get_fields().get_int_or_default("Content-Length", 0);
            }
        };

    }
}

#endif
