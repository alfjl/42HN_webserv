#ifndef WEBSERV_UTIL_IFLOW_HPP
#define WEBSERV_UTIL_IFLOW_HPP

namespace webserv {
    namespace util {

        class iflow {
        public:
            virtual bool has_next() = 0;
            virtual bool next_char(char& loc) = 0;

            char force_next_char();
        };

    }
}

#endif
