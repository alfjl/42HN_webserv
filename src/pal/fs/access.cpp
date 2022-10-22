#include "access.hpp"

#include "../../util/path.hpp"

namespace webserv {
    namespace pal {
        namespace fs {

            bool access(std::string path) {
                if (::access(path.c_str(), F_OK) == 0)
                    return true;
                return false;
            }

        }
    }
}
