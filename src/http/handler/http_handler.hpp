#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class http_handler : public webserv::util::state_machine<http_handler> {

        private:
            char                        last_char;
            std::string                 buffer;
            webserv::util::connection*  connection;

        public:
            http_handler(webserv::util::connection* new_connection) : connection(new_connection) {}

            webserv::util::wrapped_queue& in() { return connection->get_input(); }
            std::ostream& out() { return connection->get_ostream(); }

            void wait_for_char() {
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

            void start() {
                next(&http_handler::wait_for_char);
                later(&http_handler::char_arrived);
            }

            void replace(std::string& str, const std::string& from, const std::string& to) {
                while (true) {
                    size_t start_pos = str.find(from);
                    if (start_pos == std::string::npos)
                        break;
                    str.replace(start_pos, from.length(), to);
                }
            }

            void char_arrived() {
                buffer += last_char;
                if (buffer.find("\r\n\r\n") != std::string::npos) {
                    std::cout << "Processing head: " << std::endl;
                    std::cout << buffer;
                    std::string response;
                    response += "<html><head></head><body>";
                    replace(buffer, "\n", "<br/>");
                    response += buffer;
                    response += "</body></html>";
                    out() << "HTTP/1.1 200 OK\r\n";
                    out() << "Server: Webserv/0.1\r\n";
                    out() << "Content-type: text/html, text, plain\r\n";
                    out() << "Content-length: " << response.size() << "\r\n";
                    out() << "\r\n";
                    out() << response;
                    connection->close();
                    stop();
                } else {
                    next(&http_handler::start);
                }
            }

        }; // class http_handler

    } // namespace http
} // namespace webserve

#endif
