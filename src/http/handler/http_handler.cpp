#include "http_handler.hpp"

#include "../../core/routing/routing.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"
#include "../response.hpp"

namespace webserv {
    namespace http {

        http_handler::http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing)
            : connection(new_connection), routing(routing) {}

        webserv::util::wrapped_queue& http_handler::in() { return connection->get_input(); }
        std::ostream& http_handler::out() { return connection->get_ostream(); }

        void http_handler::wait_for_char() {
            if (in().has_next()) {
                if (in().next_char(last_char)) {
                    ret();
                    return;
                }
            }
            if (connection->is_closed())
                stop();
            else
                yield();
        }

        void http_handler::start() {
            next(&http_handler::wait_for_char);
            later(&http_handler::char_arrived);
        }

        void http_handler::replace(std::string& str, const std::string& from, const std::string& to) {
            while (true) {
                size_t start_pos = str.find(from);
                if (start_pos == std::string::npos)
                    break;
                str.replace(start_pos, from.length(), to);
            }
        }

        void http_handler::char_arrived() {
            buffer += last_char;
            if (buffer.find("\r\n\r\n") != std::string::npos) {
                next(&http_handler::process_head);
            } else {
                next(&http_handler::start);
            }
        }

        void http_handler::read_until_newline() {
            buffer = "";
            next(&http_handler::read_until_newline_loop);
        }

        void http_handler::read_until_newline_loop() {
            if (buffer.find("\r\n") != std::string::npos) {
                ret();
            } else {
                next(&http_handler::wait_for_char);
                later(&http_handler::read_until_newline_continue);
            }
        }

        void http_handler::read_until_newline_continue() {
            buffer += last_char;
            next(&http_handler::read_until_newline_loop);
        }

        void http_handler::parse_chunked_body() {
            next(&http_handler::read_until_newline);
            later(&http_handler::parse_chunked_body_parse_byte_count);
        }

        static bool hex2int(char c, unsigned int& i) {
                 if (c >= '0' && c <= '9') { i = c - '0'; return true; }
            else if (c >= 'a' && c <= 'f') { i = c - 'a' + 10; return true; }
            else if (c >= 'A' && c <= 'F') { i = c - 'A' + 10; return true; }
            else return false;
        }

        void http_handler::parse_chunked_body_parse_byte_count() {
            // TODO: Parse hex
            hex = 0;
            unsigned int i = 0;

            while (i < buffer.size()) {
                unsigned int h;
                if (hex2int(buffer[i], h)) {
                    hex = (hex * 16) + h;
                } else {
                    if (i == buffer.size() - 2) { // TODO: Properly check for invalid lines!
                        break;
                    } else {
                        next(&http_handler::total_failure);
                        return;
                    }
                }
                i++;
            }

            if (hex == 0) {
                ret();
            } else {
                next(&http_handler::parse_chunked_body_parse_bytes);
            }
        }

        void http_handler::parse_chunked_body_parse_bytes() {
            buffer = "";
            if (hex == 0) {
                // TODO, FIXME, XXX: Is there a trailing \r\n?
                next(&http_handler::parse_chunked_body);
            } else {
                hex--;
                next(&http_handler::wait_for_char);
                later(&http_handler::parse_chunked_body_parse_bytes_loop);
            }
        }

        void http_handler::parse_chunked_body_parse_bytes_loop() {
            buffer += last_char;
            next(&http_handler::parse_chunked_body_parse_bytes);
        }

        void http_handler::process_head() {
            std::cout << "Processing head: " << std::endl;
            std::cout << buffer;

            webserv::util::stringflow   flow(buffer);
            request_parser  parser(flow);
            into = request_core();

            bool correct = false;
            
            try {
                parse_http_request_core(parser, into);
                correct = true;
            } catch (std::runtime_error& e) {   // TODO: webserv::util::parse_exception

            }

            if (correct) {
                if (into.get_fields().get_or_default("Transfer-Encoding", "") == "chunked") {
                    next(&http_handler::parse_chunked_body);
                    later(&http_handler::process_request);
                } else {
                    next(&http_handler::process_request);
                }
            } else {
                std::cout << "Error in request!" << std::endl;
                next(&http_handler::total_failure);
            }
        }

        void http_handler::process_request() {
            std::cout << buffer << std::endl;
            std::cout << into.get_line().get_uri() << std::endl;

            response* response = routing.look_up(into);

            response->write(*connection);

            next(&http_handler::end_request);
        }

        void http_handler::end_request() {
            connection->close();

            stop();
        }

        void http_handler::total_failure() {
            std::cout << "Total failure!" << std::endl;
            next(&http_handler::end_request);
        }

    }
}
