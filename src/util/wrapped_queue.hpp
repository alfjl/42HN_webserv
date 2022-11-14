#ifndef WEBSERV_UTIL_WRAPPED_QUEUE_HPP
#define WEBSERV_UTIL_WRAPPED_QUEUE_HPP

#include "../defs.hpp"

#include "binbuf.hpp"
#include "iflow.hpp"

namespace webserv {
    namespace util {

        class wrapped_queue {
            binary_buffer buffer;
            std::stack<char> unreads;

        public:
            void push_char(char c);
            void unread_char(char c);

            bool has_next();
            bool next_char(char& loc);
        };

    }
}

#endif