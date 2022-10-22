#ifndef WEBSERV_PAL_FS_DEL_HPP
#define WEBSERV_PAL_FS_DEL_HPP

#include "../../defs.hpp"

/*
 * Thin wrapper around the C function rmdir(...)
 *                                            - nijakow
 */

namespace webserv {
    namespace pal {
        namespace fs {

            bool rmdir(std::string path);
            bool remove(std::string path);

        }
    }
}

#endif
