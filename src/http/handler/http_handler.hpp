#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class http_handler : public basic_handler {
            webserv::core::routing& _routing;
            request                 _the_request;

        public:
            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing);
            ~http_handler();

            void start() {
                // Written in inverse order due to stack
                later(&http_handler::has_more);
                later(&http_handler::process_request);
                later(&http_handler::read_request);
            }

            void read_request() {
                _the_request = request();

                later(&http_handler::read_body);
                later(&http_handler::read_fields);
            }

                void read_fields() {  // TODO: Move to basic handler
                    later(&http_handler::parse_fields);
                    later(&http_handler::read_until_rnrn);
                }

                    void read_until_rnrn() {
                        // TODO
                    }
                
                    void parse_fields() {
                        webserv::util::stringflow   flow(_buffer);
                        request_parser  parser(flow);

                        bool correct = false;
                        
                        try {
                            parse_http_request_core(parser, _the_request);
                            correct = true;
                        } catch (webserv::util::parse_exception& e) {

                        }

                        // TODO: If not correct, break out to error
                    }

                void read_body() {  // TODO: Move to basic handler
                    _body = "";

                    if (_is_normal_body()) {
                        later(&http_handler::read_normal_body);
                    } else if (_is_chunked_body()) {
                        later(&http_handler::read_chunked_body);
                    } else {
                        // No body, do nothing
                    }
                }

                    void read_normal_body() {
                        // TODO
                    }

                    void read_chunked_body() {
                        // TODO
                    }
                
                    void parse_body() {
                        _the_request.get_body() = _body;
                    }

            void process_request() {
                _routing.look_up(_the_request, this);
            }

            void has_more() {
                // TODO: Check for keep-alive
                later(&http_handler::done);
            }

            void done() {
                stop();
            }

            //                           void start();
            // enum basic_handler::abort_mode abort();

            // void char_arrived();

            // void process_head();
            // void process_request();
            // void end_request();
            // void parse_body_util();

            // webserv::core::routing& get_routing();
            // request& get_into();
        };

    }
}

#endif
