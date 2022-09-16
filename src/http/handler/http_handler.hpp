#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class http_handler : public webserv::util::state_machine {

        private:
            char                        last_char;
            std::string                 buffer;
            webserv::util::connection&  in;

        public:
            http_handler(webserv::util::connection* Conny) : in(*Conny) {} // ALF // rather use reference instead of pointer to hand it through the functions, or use shared_ptr?
            void start() {}
            void end() {}

            // void start() {
            //     next(&wait_for_char);
            //     later(&process_char);
            // }

            // void end() {
            //     if (keepalive) {
            //         next(&start);
            //     } else {
            //         close_connection();
            //     }
            // }

            // void wait_for_char() {
            //     if (!connection.has()) { 
            //         yield(&wait_for_char);
            //         return; // Give control back to multiplexer
            //     }
            //     last_char = connection.next_char();
            //     ret();
            // }

            // void process_char() {
            //     buffer.append(last_char);
            //     size_t pos = buffer.find("\r\n\r\n");
            //     if (pos != std::string::npos) {
            //         next(&parse_header_and_decide);
            //     } else {
            //         next(wait_for_char);
            //         later(&process_char);
            //     }
            // }

            // void parse_header_and_decide() {
            //     // TODO: Parse header from buffer
            //     if (expects_body()) {
            //         if (is_chunked()) {
            //             next(&parse_chunked_body);
            //         } else {
            //             next(&parse_normal_body);
            //         }
            //     }
            //     later(&process_request);
            // }

            // void parse_chunked_body() {
            //     // TODO
            //     ret();
            // }

            // void parse_normal_body() {
            //     // TODO
            //     ret();
            // }

            // void process_request() {
            //     // TODO
            //     ret();
            // }

        }; // class http_handler

    } // namespace http
} // namespace webserve

#endif
