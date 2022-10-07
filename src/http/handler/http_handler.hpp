#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "../../core/routing/routing.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class http_handler : public webserv::util::state_machine<http_handler> {
            char                        last_char;
            std::string                 buffer;
            std::string                 body;
            webserv::util::connection*  connection;
            webserv::core::routing&     routing;
            request_core                into;
            unsigned int                hex;
            unsigned int                bytes;

        public:
            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing);
            ~http_handler();

            webserv::util::wrapped_queue& in();
            std::ostream& out();

            void wait_for_char();

            void start();

            void replace(std::string& str, const std::string& from, const std::string& to);

            void char_arrived();

            void read_until_newline();
            void read_until_newline_loop();
            void read_until_newline_continue();

            void parse_normal_body();
            void parse_normal_body_loop();
            void parse_normal_body_continue();

            void parse_chunked_body();
            void parse_chunked_body_parse_byte_count();
            void parse_chunked_body_parse_bytes();
            void parse_chunked_body_parse_bytes_loop();

            void process_head();
            void process_request();
            void end_request();

            void total_failure();
        };

    }
}

#endif
