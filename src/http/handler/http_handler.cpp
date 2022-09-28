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
                std::cout << "Processing head: " << std::endl;
                std::cout << buffer;

                webserv::util::stringflow   flow(buffer);
                request_parser  parser(flow);
                request_core    into;
                
                parse_http_request_core(parser, into);

                std::cout << buffer << std::endl;
                std::cout << into.get_line().get_uri() << std::endl;

                response* response = routing.look_up(into);

                response->write(*connection);
                // std::string response;
                // response += "<html><head></head><body>";
                // replace(buffer, "\n", "<br/>");
                // response += buffer;
                // response += "</body></html>";

                // out() << "HTTP/1.1 200 OK\r\n";
                // out() << "Server: Webserv/0.1\r\n";
                // out() << "Content-type: text/html, text, plain\r\n";
                // out() << "Content-length: " << response.size() << "\r\n";
                // out() << "\r\n";
                // out() << response;
                connection->close();
                stop();
            } else {
                next(&http_handler::start);
            }
        }

    } // namespace http
} // namespace webserve
