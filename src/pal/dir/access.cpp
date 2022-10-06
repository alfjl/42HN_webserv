#include "access.hpp"

#include "../../util/path.hpp"

namespace webserv {
    namespace pal {
        namespace dir {

            int access(webserv::util::path path) {
                return (::access(path.get_addr_s().c_str(), F_OK));
            }

        }
    }
}
