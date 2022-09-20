#ifndef WEBSERV_UTIL_WRAPPED_QUEUE_HPP
#define WEBSERV_UTIL_WRAPPED_QUEUE_HPP

#include "../defs.hpp"

#include "iflow.hpp"

namespace webserv {
    namespace util {

        class wrapped_queue {
        
        private:
            std::queue<char> buffer;

        public:
            void push_char(char c);

            bool has_next();
            bool next_char(char& loc);

        }; // class wrapped_queue

    } // namespace util
} // namespace webserv

#endif