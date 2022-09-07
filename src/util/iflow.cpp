#include "../defs.hpp"

#include "iflow.hpp"

namespace webserv {
    namespace util {

        char iflow::force_next_char() {
            char c;

            if (!next_char(c))
                throw std::runtime_error("No next char!");
            
            return c;
        }

    }
}
