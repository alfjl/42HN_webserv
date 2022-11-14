#include "binbuf.hpp"

namespace webserv {
    namespace util {
        binary_buffer::binary_buffer() {

        }

        binary_buffer::binary_buffer(const binary_buffer& other) {
            chars = other.chars;
        }

        binary_buffer& binary_buffer::operator=(const binary_buffer& other) {
            chars = other.chars;
            return *this;
        }

        binary_buffer::~binary_buffer() {

        }

        void binary_buffer::clear() {
            chars.clear();
        }

        bool binary_buffer::empty() const {
            return chars.empty();
        }

        void binary_buffer::push_char(char c) {
            chars.push_back(c);
        }

        void binary_buffer::push_string(const std::string& str) {
            for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
                push_char(*it);
            }
        }

        void binary_buffer::push_cstring(const char* str) {
            for (int i = 0; str[i] != '\0'; i++) {
                push_char(str[i]);
            }
        }

        void binary_buffer::push_buffer(const char* buffer, size_t size) {
            for (size_t i = 0; i < size; i++) {
                push_char(buffer[i]);
            }
        }

        void binary_buffer::transfer(binary_buffer& into, size_type amount) {
            if (amount > chars.size()) {
                amount = chars.size();
            }

            for (size_type i = 0; i < amount; i++) {
                into.push_char(chars[i]);
            }

            chars.erase(chars.begin(), chars.begin() + amount);
        }

        void binary_buffer::transfer_all(binary_buffer& into) {
            transfer(into, chars.size());
        }

        binary_buffer::const_iterator binary_buffer::begin() const {
            return chars.begin();
        }

        binary_buffer::const_iterator binary_buffer::end() const {
            return chars.end();
        }
    }
}
