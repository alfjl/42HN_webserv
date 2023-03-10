#include "connection.hpp"

namespace webserv {
    namespace util {

        connection::connection() : out(*this), ostream(&out) {
            closed = false;
        }

        connection::~connection() {
            close();
        }

        wrapped_queue& connection::get_input() {
            return input_buffer;
        }

        wrapped_queue& connection::get_output() {
            return output_buffer;
        }

        std::ostream& connection::get_ostream() {
            return ostream;
        }

        void connection::close() {
            closed = true;
        }

        bool connection::is_closed() {
            return closed;
        }


        void connection::notify_about_close() {
            close();
        }

    }
}
