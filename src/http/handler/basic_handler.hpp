#ifndef WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP
#define WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP

#include "../../defs.hpp"

#include "../../core/routing/routing.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class basic_handler : public webserv::util::state_machine<basic_handler> {
        protected:
            char                        _last_char;
            webserv::util::connection*  _connection;
            std::string                 _buffer;
            std::string                 _body;
            request_core                _into;
            unsigned int                _hex;
            unsigned int                _bytes;

        public:
            basic_handler(webserv::util::connection* new_connection);
            virtual ~basic_handler();

            webserv::util::wrapped_queue& in();
            std::ostream& out();

            webserv::util::connection* get_connection();
            char                       get_last_char();

            virtual void wait_for_char();

            virtual void start() = 0;
            virtual void abort() = 0;

            void replace(std::string& str, const std::string& from, const std::string& to);

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

            void total_failure();
        };

    }
}

#endif
