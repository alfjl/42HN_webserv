#ifndef WEBSERV_UTIL_GENERIC_PARSER_HPP
#define WEBSERV_UTIL_GENERIC_PARSER_HPP

#include "../defs.hpp"
#include "iflow.hpp"

namespace webserv {
    namespace util {

        class parser : public iflow {
        private:
            iflow&  flow;

            bool this_char(char& loc);

        public:
            parser(iflow& flow);
            ~parser();

            bool has_next();
            bool next_char(char& loc);

            bool check(char c);
            bool checks(std::string text);
        };


    }
}

#endif
