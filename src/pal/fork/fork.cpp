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


            fork_task::fork_task(std::string executable) : _executable(executable) {

            }

            fork_task::~fork_task() {

            }

            void fork_task::do_child_stuff() {
                const char** argv = (const char**) ::malloc(sizeof(char*) * 2);

                if (argv != NULL) {
                    argv[0] = _executable.c_str();
                    argv[1] = NULL;

                    const char** envp = (const char**) ::malloc(sizeof(char*) * 1);
                    if (envp != NULL) {
                        envp[0] = NULL;

                        ::execve(argv[0], (char *const*) argv, (char *const*) envp);
                    }
                }
                exit(127);
            }

            pid_t fork_task::perform() {
                std::pair<fork_status, pid_t> result = fork();

                switch (result.first) {
                    case fork_status_i_am_parent:
                        return result.second;
                    case fork_status_i_am_child:
                        do_child_stuff();
                        break;
                    default:
                        throw std::runtime_error("Something went wrong with fork()!");
                }

                return 0;
            }

        }
    }
}
