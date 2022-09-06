#include "parser.hpp"

namespace webserv {
    namespace util {

        parser::parser(iflow& _flow) : flow(_flow) {

        }

        parser::~parser() {

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

        bool parser::check(char c) {
            char other;

            return (this_char(other) && (other == c));
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
                    return true;
                }
            }
            return true;
        }

    }
}
