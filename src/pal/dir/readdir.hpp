#ifndef WEBSERV_PAL_DIR_READDIR_HPP
#define WEBSERV_PAL_DIR_READDIR_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace dir {

            class readdir {

                readdir() {}
                ~readdir() {}

                std::vector<std::string> readdir_r(const std::string& dir);

            }; // class readdir

        } // namespace dir
    } // namespace pal
} // namespace webserv

#endif
