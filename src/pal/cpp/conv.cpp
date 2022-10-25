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

            static bool hexchar2int(char c, unsigned int& i) {
                     if (c >= '0' && c <= '9') { i = c - '0'; return true; }
                else if (c >= 'a' && c <= 'f') { i = c - 'a' + 10; return true; }
                else if (c >= 'A' && c <= 'F') { i = c - 'A' + 10; return true; }
                else return false;
            }

            bool hex_string_to_uint(std::string _buffer, unsigned int& value) {
                unsigned int _hex = 0;
                unsigned int i    = 0;

                if (_buffer.size() == 0) return false;

                while (i < _buffer.size()) {
                    unsigned int h;
                    if (hexchar2int(_buffer[i], h)) {
                        _hex = (_hex * 16) + h;
                    } else {
                        if (i > 0 && i == _buffer.size() - 2) { // TODO: Properly check for invalid lines!
                            break;
                        } else {
                            return false;
                        }
                    }
                    i++;
                }

                value = _hex;
                return true;
            }

        }
    }
}
