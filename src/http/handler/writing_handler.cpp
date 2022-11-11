#include "writing_handler.hpp"


namespace webserv {
    namespace http {

        writing_handler::writing_handler(std::string text, webserv::util::connection* connection) : basic_handler(connection), _text(text), _index(0) {

        }

        writing_handler::~writing_handler() {
            get_connection()->close();
        }

        void writing_handler::start() {
            later(&writing_handler::done);
            later(&writing_handler::restart);
        }

            void writing_handler::done() {
                stop();
            }

                void writing_handler::restart() {
                    if (!get_connection()->is_closed() && _index < _text.size()) {
                        get_connection()->get_ostream() << _text[_index++];
                        later(&writing_handler::restart);
                        if (_index % 1000 == 0) yield();
                    }
                }

            void writing_handler::parse_fields() {
                // Do nothing!
            }

            void writing_handler::read_chunked_body__parse_hex() {
                // Do nothing!
            }

            enum basic_handler::abort_mode writing_handler::abort() {
                // Do nothing!
                return abort_mode_terminate;
            }

            unsigned int writing_handler::get_normal_body_size() {
                // Do nothing!
                return 0;
            }

    }
}