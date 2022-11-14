#include "wrapped_queue.hpp"

namespace webserv {
    namespace util {

        void wrapped_queue::push_char(char c) {
            buffer.push(c);
        }

        void wrapped_queue::unread_char(char c) {
            unreads.push(c);
        }


        bool wrapped_queue::has_next() {
            return (!buffer.empty() || !unreads.empty());
        }

        bool wrapped_queue::next_char(char& loc) {
            if (!unreads.empty()) {
                loc = unreads.top();
                unreads.pop();
                return true;
            } else if (!buffer.empty()) {
                loc = buffer.pop();
                return true;
            }
            return false;
        }

    }
}