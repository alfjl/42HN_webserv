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

        binary_buffer::size_type binary_buffer::size() const {
            return chars.size();
        }

        bool binary_buffer::empty() const {
            return chars.empty();
        }

        void binary_buffer::clear() {
            chars.clear();
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

        void binary_buffer::push(char c) { push_char(c); }
        void binary_buffer::push(const std::string& str) { push_string(str); }
        void binary_buffer::push(const char* str) { push_cstring(str); }
        void binary_buffer::push(const char* buffer, size_t size) { push_buffer(buffer, size); }
        void binary_buffer::push(const binary_buffer& other) {
            for (binary_buffer::const_iterator it = other.begin(); it != other.end(); ++it) {
                push_char(*it);
            }
        }

        void binary_buffer::assign(char c) { clear(); push_char(c); }
        void binary_buffer::assign(const std::string& str) { clear(); push_string(str); }
        void binary_buffer::assign(const char* str) { clear(); push_cstring(str); }
        void binary_buffer::assign(const char* buffer, size_t size) { clear(); push_buffer(buffer, size); }
        void binary_buffer::assign(const binary_buffer& other) { clear(); push(other); }

        char binary_buffer::pop() {
            if (empty())
                throw std::runtime_error("Cannot pop from empty buffer!");
            char c = chars.front();
            chars.erase(chars.begin());
            return c;
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

        void binary_buffer::write_to_stream(std::ostream& stream) const {
            for (const_iterator it = begin(); it != end(); ++it) {
                stream << *it;
            }
        }

        /*
         * WATCH OUT: '\0' characters will *NOT* be copied!
         */
        std::string binary_buffer::to_string() const {
            std::ostringstream stream;
            write_to_stream(stream);
            return stream.str();
        }

        binary_buffer::const_iterator binary_buffer::begin() const {
            return chars.begin();
        }

        binary_buffer::const_iterator binary_buffer::end() const {
            return chars.end();
        }

        bool binary_buffer::detect_and_cut_crlf() {
            if (chars.size() < 2) {
                return false;
            }

            if (chars[chars.size() - 2] == '\r' && chars[chars.size() - 1] == '\n') {
                chars.erase(chars.end() - 2, chars.end());
                return true;
            }

            return false;
        }
    }
}
