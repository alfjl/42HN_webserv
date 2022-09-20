#include "wrapped_queue.hpp"

namespace webserv {
    namespace util {

        void wrapped_queue::push_char(char c) {
            buffer.push(c);
        }


        bool wrapped_queue::has_next() {
            return (!buffer.empty());
        }

        bool wrapped_queue::next_char(char& loc) {
            if (has_next()) {
                loc = buffer.front();
                buffer.pop();
                return true;
            }
            return false;
        }

    } // namespace util
} // namespace webserv