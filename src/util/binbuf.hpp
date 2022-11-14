#ifndef WEBSERV_UTIL_BINBUF_HPP
#define WEBSERV_UTIL_BINBUF_HPP

#include "../defs.hpp"

namespace webserv {
    namespace util {

        class binary_buffer {
            std::vector<char> chars;

        public:
            typedef std::vector<char>::size_type size_type;
            typedef std::vector<char>::iterator iterator;
            typedef std::vector<char>::const_iterator const_iterator;

            binary_buffer();
            binary_buffer(const binary_buffer& other);
            binary_buffer& operator=(const binary_buffer& other);
            ~binary_buffer();

            void clear();
            bool empty() const;

            void push_char(char c);
            void push_string(const std::string& str);
            void push_cstring(const char* str);
            void push_buffer(const char* buffer, size_t size);

            const_iterator begin() const;
            const_iterator end() const;
        };

    }
}

#endif
