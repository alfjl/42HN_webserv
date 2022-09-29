#include "parser.hpp"

#include "../defs.hpp"

namespace webserv {
    namespace util {

        parser::parser(iflow& _flow) : flow(_flow) {

        }

        parser::~parser() {

        }

        void parser::parse_error(std::string message) {
            throw std::runtime_error(message);
        }

        bool parser::has_next() {
            return ((!pushbacks.empty()) || flow.has_next());
        }

        bool parser::next_char(char& loc) {
            if (!pushbacks.empty()) {
                loc = pushbacks.top();
                pushbacks.pop();
                return true;
            }
            return flow.next_char(loc);
        }

        bool parser::this_char(char& loc) {
            char c;

            if (!next_char(c))
                return false;
            loc = c;
            pushbacks.push(c);
            return true;
        }

        bool parser::check_noadvance(char c) {
            char loc;

            if (this_char(loc)) {
                return c == loc;
            }

            return false;
        }

        bool parser::check(char c) {
            char other;

            if (this_char(other) && (other == c)) {
                next_char(other);
                return true;
            }
            return false;
        }

        bool parser::check_one_of(std::string c, char& which) {
            std::string::iterator it = c.begin();
            while (it != c.end()) {
                if (check(*it)) {
                    which = *it;
                    return true;
                }
                ++it;
            }
            return false;
        }

        bool parser::checks(std::string text) {
            std::vector<char> chars;

            for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
                char c;
                bool r;
                
                r = next_char(c);
                if (r) {
                    chars.push_back(c);
                }

                if ((!r) || c != *it) {
                    for (std::vector<char>::iterator ci = chars.begin(); ci != chars.end(); ++ci)
                        pushbacks.push(*ci);
                    return false;
                }
            }
            return true;
        }

        bool parser::check_uint(unsigned int& value) {
            unsigned int  i = 0;
            unsigned int  chars = 0;
            char          which;

            while (check_one_of("0123456789", which)) {
                i = (i * 10) + (which - '0');
                chars++;
            }

            value = i;

            return chars > 0;
        }

        void parser::expect(char c) {
            if (!check(c))
                parse_error("Expected a different character!");
        }

        void parser::expects(std::string text) {
            if (!checks(text))
                parse_error("Expected a different string!");
        }

        void parser::expect_uint(unsigned int& value) {
            if (!check_uint(value))
                parse_error("Expected an integer!");
        }

        void parser::skip_spaces() {
            while (check(' '));
        }

    }
}
