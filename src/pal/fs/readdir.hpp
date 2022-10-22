#ifndef WEBSERV_PAL_FS_READDIR_HPP
#define WEBSERV_PAL_FS_READDIR_HPP

#include "../../defs.hpp"

/*
 * Thin wrapper around the C functions of dirent.h
 * 
 *                                            - alanghan
 */

namespace webserv {
    namespace pal {
        namespace fs {

            std::vector<std::string> read_directory(std::string path);

            bool is_directory(std::string entry);

        }
    }
}

#endif
