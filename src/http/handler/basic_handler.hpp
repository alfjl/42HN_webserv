#ifndef WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP
#define WEBSERV_basic_HANDLER_BASIC_HANDLER_HPP

#include "../../defs.hpp"

#include "../../core/routing/routing.hpp"
#include "../../pal/cpp/optional.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

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

            struct connection_config          _connection_configs;

            unsigned int                      _read_normal_body__expected_size; 
            std::string                       _read_normal_body__result;

            std::string                       _read_chunked_body__result;

            std::string                       _read_until_rn__buffer;
            std::string                       _read_until_rnrn__buffer;

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



           /*
             *
             *     S t a t e   M a c h i n e   F u n c t i o n s
             *
             */

            void read_next_char();

                void read_fields();

                    void read_until_rnrn();

                        void read_until_rnrn__restart();

                        void read_until_rnrn__continue();

                    virtual void parse_fields() = 0;

                        void read_until_rn();

                            void read_until_rn__restart();

                            void read_until_rn__continue();

                    void read_normal_body();

                        void read_normal_body__restart();

                        void read_normal_body__continue();

                    void read_chunked_body();

                        void read_chunked_body__restart();

                        bool parse_hex();

                        virtual void read_chunked_body__parse_hex() = 0;

                        void read_chunked_body__continue();

            virtual enum abort_mode abort() = 0;

            void perform_abort();

            void total_failure();

            void parse_error();

            void done();

            virtual void has_more();



            /*
             *
             *     U t i l i t i e s
             *
             */

            bool _is_normal_body();

            virtual unsigned int get_normal_body_size() = 0;
        };

    }
}

#endif
