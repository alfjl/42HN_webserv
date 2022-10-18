#include "basic_handler.hpp"

#include "../../core/routing/routing.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"
#include "../response.hpp"

namespace webserv {
    namespace http {

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
        char                       basic_handler::get_last_char()  { return _last_char;  }


        void basic_handler::wait_for_char() {
            if (in().has_next()) {
                if (in().next_char(_last_char)) {
                    ret();
                    return;
                }
            }
            if (_connection->is_closed())
                stop();
            else
                yield();
        }

       void basic_handler::replace(std::string& str, const std::string& from, const std::string& to) {
            while (true) {
                size_t start_pos = str.find(from);
                if (start_pos == std::string::npos)
                    break;
                str.replace(start_pos, from.length(), to);
            }
        }

        void basic_handler::read_until_newline() {
            _buffer = "";
            next(&basic_handler::read_until_newline_loop);
        }

        void basic_handler::read_until_newline_loop() {
            if (_buffer.find("\r\n") != std::string::npos) {
                ret();
            } else {
                next(&basic_handler::wait_for_char);
                later(&basic_handler::read_until_newline_continue);
            }
        }

        void basic_handler::read_until_newline_continue() {
            _buffer += basic_handler::get_last_char();
            next(&basic_handler::read_until_newline_loop);
        }

        void basic_handler::parse_normal_body() {
            next(&basic_handler::parse_normal_body_loop);
        }

        void basic_handler::parse_normal_body_loop() {
            if (_bytes == 0) ret();
            else {
                _bytes--;
                next(&basic_handler::wait_for_char);
                later(&basic_handler::parse_normal_body_continue);
            }
        }

        void basic_handler::parse_normal_body_continue() {
            _body += basic_handler::get_last_char();
            next(&basic_handler::parse_normal_body_loop);
        }

        void basic_handler::parse_chunked_body() {
            next(&basic_handler::read_until_newline);
            later(&basic_handler::parse_chunked_body_parse_byte_count);
        }

        static bool hex2int(char c, unsigned int& i) {
                 if (c >= '0' && c <= '9') { i = c - '0'; return true; }
            else if (c >= 'a' && c <= 'f') { i = c - 'a' + 10; return true; }
            else if (c >= 'A' && c <= 'F') { i = c - 'A' + 10; return true; }
            else return false;
        }

        void basic_handler::parse_chunked_body_parse_byte_count() {
            _hex = 0;
            unsigned int i = 0;

            while (i < _buffer.size()) {
                unsigned int h;
                if (hex2int(_buffer[i], h)) {
                    _hex = (_hex * 16) + h;
                } else {
                    if (i > 0 && i == _buffer.size() - 2) { // TODO: Properly check for invalid lines!
                        break;
                    } else {
                        next(&basic_handler::total_failure);
                        return;
                    }
                }
                i++;
            }

            _buffer = "";
            if (_hex == 0) {
                ret();
            } else {
                next(&basic_handler::parse_chunked_body_parse_bytes);
            }
        }

        void basic_handler::parse_chunked_body_parse_bytes() {
            _buffer = "";
            if (_hex == 0) {
                // TODO, FIXME, XXX: Is there always a trailing \r\n?
                next(&basic_handler::read_until_newline);
                later(&basic_handler::parse_chunked_body);
            } else {
                _hex--;
                next(&basic_handler::wait_for_char);
                later(&basic_handler::parse_chunked_body_parse_bytes_loop);
            }
        }

        void basic_handler::parse_chunked_body_parse_bytes_loop() {
            _body += basic_handler::get_last_char();
            next(&basic_handler::parse_chunked_body_parse_bytes);
        }

        void basic_handler::total_failure() {
            std::cout << "Total failure!" << std::endl;
            next(&basic_handler::abort); // WATCH OUT!!! FIXME, ERROR, XXX! Create a virtual getter!
        }

    }
}