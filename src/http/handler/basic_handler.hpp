#ifndef WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP
#define WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP

#include "../../defs.hpp"

#include "../../core/routing/routing.hpp"
#include "../../pal/cpp/optional.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"
// #include "../proto/request.hpp"

namespace webserv {
    namespace http {


        struct connection_config {
            webserv::pal::cpp::optional<unsigned int>    _max_len;
        };

        class basic_handler : public webserv::util::state_machine {
        protected:
            webserv::pal::cpp::optional<char> _last_char;
            webserv::util::connection*        _connection;
            std::string                       _buffer;
            std::string                       _body;
            unsigned int                      _hex;
            unsigned int                      _bytes;

            struct connection_config    _connection_configs;

            unsigned int            _read_normal_body__expected_size; // auslagern basic_handler?    
            std::string             _read_normal_body__result;

            std::string             _read_chunked_body__result;

            std::string             _read_until_rn__buffer;
            std::string             _read_until_rnrn__buffer;

            enum abort_mode {
                abort_mode_continue,
                abort_mode_terminate
            };

        public:
            /*
             *
             *     C o n s t r u c t o r s ,   G e t t e r s   a n d   S e t t e r s
             *
             */

            basic_handler(webserv::util::connection* new_connection);
            virtual ~basic_handler();

            webserv::util::wrapped_queue& in();
            std::ostream& out();

            webserv::util::connection* get_connection();
            struct connection_config*  get_connection_configs();

            void read_next_char();

                void read_fields() {
                    later(&basic_handler::parse_fields);
                    later(&basic_handler::read_until_rnrn);
                }

                virtual void parse_fields() = 0;

                    void read_until_rn() {
                        _read_until_rn__buffer = "";
                        later(&basic_handler::read_until_rn__restart);
                    }

                        void read_until_rn__restart() {
                            later(&basic_handler::read_until_rn__continue);
                            later(&basic_handler::read_next_char);
                        }

                        void read_until_rn__continue() {
                            if (_last_char.enabled()) {
                                _read_until_rn__buffer += _last_char.value();
                                if (_read_until_rn__buffer.find("\r\n") != std::string::npos) {
                                    // We return: Do nothing!
                                    _read_until_rn__buffer = _read_until_rn__buffer.substr(0, _read_until_rn__buffer.size() - 2);
                                    return;
                                } else {
                                    later(&basic_handler::read_until_rn__restart);
                                }
                            } else {
                                // We return: Do nothing!
                                return;
                            }
                        }

                            void read_until_rnrn() {
                                _read_until_rnrn__buffer = "";
                                later(&basic_handler::read_until_rnrn__restart);
                            }

                                void read_until_rnrn__restart() {
                                    later(&basic_handler::read_until_rnrn__continue);
                                    later(&basic_handler::read_until_rn);
                                }

                                void read_until_rnrn__continue() {
                                    if (_read_until_rn__buffer != "") {
                                        _read_until_rnrn__buffer += _read_until_rn__buffer;
                                        _read_until_rnrn__buffer += "\r\n";
                                        later(&basic_handler::read_until_rnrn__restart);
                                    } else {
                                        _read_until_rnrn__buffer += "\r\n";
                                        // This "function" returns here: Do nothing!
                                        return;
                                    }
                                }

                    void read_normal_body() {
                        _read_normal_body__result = "";
                        later(&basic_handler::read_normal_body__restart);
                    }

                        void read_normal_body__restart() {
                            if (_read_normal_body__expected_size > 0) {
                                later(&basic_handler::read_normal_body__continue);
                                later(&basic_handler::read_next_char);
                            } else {
                                // This "function" returns here: Do nothing!
                                return;
                            }
                        }

                        void read_normal_body__continue() {
                            if (_last_char.enabled()) {
                                _read_normal_body__expected_size--;
                                _read_normal_body__result += _last_char.value();
                                later(&basic_handler::read_normal_body__restart);
                            } else {
                                // This "function" returns here: Do nothing!
                                return;
                            }
                        }

                    void read_chunked_body() {
                        _read_chunked_body__result = "";
                        later(&basic_handler::read_chunked_body__restart);
                    }

                        void read_chunked_body__restart() {
                            later(&basic_handler::read_chunked_body__parse_hex);
                            later(&basic_handler::read_until_rn);
                        }

                        virtual void read_chunked_body__parse_hex() = 0;

                        void read_chunked_body__continue() {
                            // TODO: Check how many bytes we have actually read
                            _read_chunked_body__result += _read_normal_body__result;
                            later(&basic_handler::read_chunked_body__restart);
                        }

            // webserv::pal::cpp::optional<char> get_last_char();

            // virtual void wait_for_char();

            // virtual void start() = 0;
            virtual enum abort_mode abort() = 0;
            void perform_abort();

            // void replace(std::string& str, const std::string& from, const std::string& to);

            // void read_until_newline();
            // void read_until_newline_loop();
            // void read_until_newline_continue();

            // void parse_normal_body();
            // void parse_normal_body_loop();
            // void parse_normal_body_continue();

            // void parse_chunked_body();
            // void parse_chunked_body_parse_byte_count();
            // void parse_chunked_body_parse_bytes();
            // void parse_chunked_body_parse_bytes_loop();

            void total_failure();
        };

    }
}

#endif
