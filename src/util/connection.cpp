#include "connection.hpp"

namespace webserv {
    namespace util {

        connection::connection() {
            closed = false;
        }

        void connection::push_char(char c) {
            buffer.push(c);
        }


        bool connection::has_next() {
            return (!buffer.empty());
        }

        bool connection::next_char(char& loc) {
            if (has_next()) {
                loc = buffer.front();
                buffer.pop();
                return true;
            }
            return false;
        }


        void connection::close() {
            closed = true;
        }

        bool connection::is_closed() {
            return closed;
        }

    }
}
