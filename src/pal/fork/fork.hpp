#ifndef WEBSERV_PAL_FORK_FORK_HPP
#define WEBSERV_PAL_FORK_FORK_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace fork {

            enum fork_status {
                fork_status_boom,
                fork_status_i_am_parent,
                fork_status_i_am_child
            };

            std::pair<fork_status, pid_t> fork();

            class fork_task {
            public:
            };

        }
    }
}

#endif
