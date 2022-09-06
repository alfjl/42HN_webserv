#include "parser.hpp"

namespace webserv {
    namespace util {

        parser::parser(iflow& _flow) : flow(_flow) {

        }

        parser::~parser() {

        }

        bool parser::has_next() {
            return flow.has_next();
        }

        bool parser::next_char(char& loc) {
            return flow.next_char(loc);
        }

        bool parser::this_char(char& loc) {
            // TODO
            return false;
        }

        bool parser::check(char c) {
            char other;

            return (this_char(other) && (other == c));
        }

        bool parser::checks(std::string text) {
            // TODO
            return false;
        }

    }
}
