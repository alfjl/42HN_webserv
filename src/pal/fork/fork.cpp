#include "fork.hpp"

namespace webserv {
    namespace pal {
        namespace fork {

            static fork_status fork_status_for(pid_t pid) {
                     if (pid <  0) return fork_status_boom;
                else if (pid == 0) return fork_status_i_am_child;
                else               return fork_status_i_am_parent;
            }

            std::pair<fork_status, pid_t> fork() {
                pid_t pid = ::fork();

                return std::make_pair<fork_status, pid_t>(fork_status_for(pid), pid);
            }

        }
    }
}
