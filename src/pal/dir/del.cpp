#include "del.hpp"

namespace webserv {
    namespace pal {
        namespace dir {

            bool rmdir(std::string path) {
                return ::rmdir(path.c_str()) == 0;
            }

        }
    }
}
