#include "fork.hpp"

namespace webserv {
    namespace pal {
        namespace fork {

            bool safe_pipe(int* pipe_in, int* pipe_out) {
                int fds[2];

                if (::pipe(fds) != 0) return false;
                else {
                    *pipe_in  = fds[1];
                    *pipe_out = fds[0];
                }
                
                return true;
            }

            bool safe_dup2(int overridden_fd, int original_fd) {
                return (::dup2(original_fd, overridden_fd) >= 0);
            }

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

                        if (_input_to.enabled())  safe_dup2(STDIN_FILENO,  _input_to.value());
                        if (_output_to.enabled()) safe_dup2(STDOUT_FILENO, _output_to.value());

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

            void fork_task::input_to(int input) {
                _input_to.enable(input);
            }

            void fork_task::output_to(int output) {
                _output_to.enable(output);
            }

            void fork_task::io_to(int input, int output) {
                input_to(input);
                output_to(output);
            }

        }
    }
}
