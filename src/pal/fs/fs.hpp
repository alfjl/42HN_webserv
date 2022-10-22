#ifndef WEBSERV_PAL_FS_FS_HPP
#define WEBSERV_PAL_FS_FS_HPP

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

			bool rmdir(std::string path);
            bool remove(std::string path);

			bool access(std::string path);

        }
    }
}

#endif