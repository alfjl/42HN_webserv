#include "basic_handler.hpp"

#include "../../core/routing/routing.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"
#include "../proto/response.hpp"

namespace webserv {
    namespace http {

        /*
         *
         *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
         *
         */
        basic_handler::basic_handler(webserv::util::connection* new_connection)
            : _connection(new_connection) {
            if (_connection != NULL)
                _connection->increment_refcount();
        }

        basic_handler::~basic_handler() {
            if (_connection != NULL)
                _connection->decrement_refcount();
        }

        webserv::util::wrapped_queue& basic_handler::in() { return _connection->get_input(); }
        std::ostream& basic_handler::out() { return _connection->get_ostream(); }

        webserv::util::connection* basic_handler::get_connection() { return _connection; }
        struct connection_config*  basic_handler::get_connection_configs() { return &_connection_configs; }



        /*
         *
         *     S t a t e   M a c h i n e   F u n c t i o n s
         *
         */
        void basic_handler::read_next_char() {
            char c;

            if (in().has_next() && in().next_char(c))
                _last_char.enable(c);
            else if (_connection->is_closed())
                _last_char.disable();
            else {
                later(&basic_handler::read_next_char);
                yield();
            }
        }

                void basic_handler::read_fields() {
                    later(&basic_handler::parse_fields);
                    later(&basic_handler::read_until_rnrn);
                }

                    void basic_handler::read_until_rnrn() {
                        _read_until_rnrn__buffer.clear();
                        later(&basic_handler::read_until_rnrn__restart);
                    }

                        void basic_handler::read_until_rnrn__restart() {
                            later(&basic_handler::read_until_rnrn__continue);
                            later(&basic_handler::read_until_rn);
                        }

                        void basic_handler::read_until_rnrn__continue() {
                            if (!_read_until_rn__buffer.empty()) {
                                _read_until_rnrn__buffer.push(_read_until_rn__buffer);
                                _read_until_rnrn__buffer.push("\r\n");
                                later(&basic_handler::read_until_rnrn__restart);
                            } else {
                                _read_until_rnrn__buffer.push("\r\n");
                                // This "function" returns here: Do nothing!
                                return;
                            }
                        }

                        void basic_handler::read_until_rn() {
                            _read_until_rn__buffer.clear();
                            later(&basic_handler::read_until_rn__restart);
                        }

                            void basic_handler::read_until_rn__restart() {
                                later(&basic_handler::read_until_rn__continue);
                                later(&basic_handler::read_next_char);
                            }

                            void basic_handler::read_until_rn__continue() {
                                if (_last_char.enabled()) {
                                    _read_until_rn__buffer.push(_last_char.value());
                                    if (_read_until_rn__buffer.detect_and_cut_crlf()) {
                                        // We return: Do nothing!
                                        return;
                                    } else {
                                        later(&basic_handler::read_until_rn__restart);
                                    }
                                } else {
                                    // We return: Do nothing!
                                    return;
                                }
                            }

                    void basic_handler::read_normal_body() {
                        _read_normal_body__result.clear();
                        later(&basic_handler::read_normal_body__restart);
                    }

                        void basic_handler::read_normal_body__restart() {
                            if (_read_normal_body__expected_size > 0) {
                                later(&basic_handler::read_normal_body__continue);
                                later(&basic_handler::read_next_char);
                            } else {
                                // This "function" returns here: Do nothing!
                                return;
                            }
                        }

                        void basic_handler::read_normal_body__continue() {
                            if (_last_char.enabled()) {
                                _read_normal_body__expected_size--;
                                _read_normal_body__result.push(_last_char.value());
                                later(&basic_handler::read_normal_body__restart);
                            } else {
                                // This "function" returns here: Do nothing!
                                return;
                            }
                        }

                    void basic_handler::read_chunked_body() {
                        _read_chunked_body__result.clear();
                        later(&basic_handler::read_chunked_body__restart);
                    }

                        bool basic_handler::parse_hex() {
                            unsigned int hex;

                            if (webserv::pal::cpp::hex_string_to_uint(_read_until_rn__buffer.to_string(), hex)) {
                                if (hex == 0) {
                                    return true;
                                } else {
                                    _read_normal_body__expected_size = hex;
                                    later(&basic_handler::read_chunked_body__continue);
                                    later(&basic_handler::read_until_rn);
                                    later(&basic_handler::read_normal_body);
                                    return true;
                                }
                            }
                            return false;
                        }

                        void basic_handler::read_chunked_body__restart() {
                            later(&basic_handler::read_chunked_body__parse_hex);
                            later(&basic_handler::read_until_rn);
                        }

                        void basic_handler::read_chunked_body__continue() {
                            _read_chunked_body__result.push(_read_normal_body__result);
                            later(&basic_handler::read_chunked_body__restart);
                        }

        void basic_handler::perform_abort() {
            if (abort() == abort_mode_terminate)
                stop();
        }

        void basic_handler::total_failure() {
            later(&basic_handler::perform_abort);
        }

            void basic_handler::parse_error() {
                later(&basic_handler::done);
            }

            void basic_handler::done() {
                basic_handler::get_connection()->close();
                stop();
            }

            void basic_handler::has_more() {
                later(&basic_handler::done);
            }



            /*
             *
             *     U t i l i t i e s
             *
             */

            bool basic_handler::_is_normal_body() {
                return get_normal_body_size() > 0;
            }

    }
}
