#include "conv.hpp"

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace cpp {

            bool is_inbounds_for_int(long val) {
                return val >= std::numeric_limits<int>::min() && val <= std::numeric_limits<int>::max();
            }

            bool string_to_int(const char* text, int& loc) {
                char* endptr = (char*) text;

                long int li = strtol(text, &endptr, 10);

                loc = (int) li;

                return (endptr != NULL && *endptr == '\0') && is_inbounds_for_int(li);
            }

            std::string int_to_string(unsigned int code){
                std::ostringstream ost;
                ost << code;
                return ost.str();
            }

        }
    }
}
