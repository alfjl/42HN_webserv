#ifndef WEBSERV_PAL_FORK_FORK_HPP
#define WEBSERV_PAL_FORK_FORK_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace fork {

            bool safe_pipe(int* pipe_in, int* pipe_out);

            enum fork_status {
                fork_status_boom,
                fork_status_i_am_parent,
                fork_status_i_am_child
            };

            std::pair<fork_status, pid_t> fork();

            class fork_task {
                std::string _executable;

                void do_child_stuff();

            public:
                fork_task(std::string executable);
                ~fork_task();

                pid_t perform();
            };

        }
    }
}

#endif
