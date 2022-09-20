#include "connection.hpp"

namespace webserv {
    namespace util {

        connection::connection() {
            closed = false;
        }

        wrapped_queue& connection::get_input() {
            return input_buffer;
        }

        wrapped_queue& connection::get_output() {
            return output_buffer;
        }


        void connection::close() {
            closed = true;
        }

        bool connection::is_closed() {
            return closed;
        }


        void connection::react_close() {
            close();
        }

    } // namespace util
} // namespace webserv
