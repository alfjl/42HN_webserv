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

            size_type size() const;
            bool empty() const;

            void clear();

            void push_char(char c);
            void push_string(const std::string& str);
            void push_cstring(const char* str);
            void push_buffer(const char* buffer, size_t size);

            void push(char c);
            void push(const std::string& str);
            void push(const char* str);
            void push(const char* buffer, size_t size);
            void push(const binary_buffer& other);

            char pop();

            void assign(char c);
            void assign(const std::string& str);
            void assign(const char* str);
            void assign(const char* buffer, size_t size);
            void assign(const binary_buffer& other);

            void transfer(binary_buffer& into, size_type amount);
            void transfer_all(binary_buffer& into);

            void write_to_stream(std::ostream& stream) const;
            std::string to_string() const;

            const_iterator begin() const;
            const_iterator end() const;
        };

    }
}

#endif
