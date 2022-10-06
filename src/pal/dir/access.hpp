#ifndef WEBSERV_PAL_DIR_ACCESS_HPP
#define WEBSERV_PAL_DIR_ACCESS_HPP

#include "../../defs.hpp"

/*
 * Thin wrapper around the C function access(...)
 *                                            - alanghan
 */

namespace webserv {
    namespace pal {
        namespace dir {

            int access(webserv::util::path path);

        }
    }
}

#endif