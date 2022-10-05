#ifndef WEBSERV_PAL_ENV_HPP
#define WEBSERV_PAL_ENV_HPP

#include "../../defs.hpp"

#include "../../util/path.hpp"

namespace webserv {
    namespace pal {
        namespace env {

           std::string getenv(std::string var);
		   webserv::util::path pwd();

        }
    }
}

#endif
