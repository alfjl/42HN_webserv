#include "access.hpp"

#include "../../util/path.hpp"

namespace webserv {
    namespace pal {
        namespace dir {

            int access(std::string path) {
                return (::access(path.c_str(), F_OK));
            }

        }
    }
}
