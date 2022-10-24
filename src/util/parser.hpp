#ifndef WEBSERV_UTIL_GENERIC_PARSER_HPP
#define WEBSERV_UTIL_GENERIC_PARSER_HPP

#include "../defs.hpp"

#include "iflow.hpp"

namespace webserv {
    namespace util {

        class parse_exception : public std::exception {
            std::string _message;

        public:
            parse_exception(std::string message);
            ~parse_exception() _NOEXCEPT;

            const char* what() const _NOEXCEPT;
        };

        class parser : public iflow {
            iflow&            flow;
            std::stack<char>  pushbacks;

        protected:
            bool this_char(char& loc);

        public:
            parser(iflow& flow);
            ~parser();

            void parse_error(std::string message);

            bool has_next();
            bool next_char(char& loc);

            bool check_noadvance(char c);
            bool check(char c);
            bool check_one_of(std::string c, char& which);
            bool checks(std::string text);
            bool check_uint(unsigned int& value);

            void expect(char c);
            void expects(std::string text);
            unsigned int expect_uint();

            void skip_spaces();
        };

    }
}

#endif
