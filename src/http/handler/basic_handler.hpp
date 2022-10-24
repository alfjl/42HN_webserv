#ifndef WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP
#define WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP

#include "../../defs.hpp"

#include "../../core/routing/routing.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace http {


        struct connection_config {
            webserv::pal::cpp::optional<unsigned int>    _max_len;
        };

        class basic_handler : public webserv::util::state_machine {
        protected:
            char                        _last_char;
            webserv::util::connection*  _connection;
            std::string                 _buffer;
            std::string                 _body;
            unsigned int                _hex;
            unsigned int                _bytes;

            struct connection_config    _connection_configs;

            enum abort_mode {
                abort_mode_continue,
                abort_mode_terminate
            };

        public:
            basic_handler(webserv::util::connection* new_connection);
            virtual ~basic_handler();

            webserv::util::wrapped_queue& in();
            std::ostream& out();

            webserv::util::connection* get_connection();
            struct connection_config*  get_connection_configs();
            char                       get_last_char();

            virtual void wait_for_char();

            virtual void start() = 0;
            virtual enum abort_mode abort() = 0;
            void perform_abort();

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
