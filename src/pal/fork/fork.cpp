#include "fork.hpp"

#include "../fs/fs.hpp"

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

            

            wait_set::wait_set() {

            }

            wait_set::~wait_set() {
                // NOTE: This set should not be empty!
            }

            void wait_set::add(pid_t pid) {
                pids.insert(pid);
            }

            bool wait_set::wait_for(pid_t pid) {
                if (pids.find(pid) == pids.end())
                    throw std::runtime_error("PID is not in wait_set!");
                // TODO: Extract return code
                if (::waitpid(pid, NULL, 0) >= 0) {
                    pids.erase(pid);
                    return true;
                }
                return false;
            }

            void wait_set::wait_for_all() {
                while (!pids.empty()) {
                    wait_set::wait_for(*pids.begin());
                }
            }


            fork_task::fork_task(std::string executable) : _executable(executable) {

            }

            fork_task::~fork_task() {

            }

            void fork_task::do_child_stuff() {
                std::vector<int>::const_iterator it = _to_close.begin();
                while (it != _to_close.end()) {
                    webserv::pal::fs::close(*it);
                    ++it;
                }

                const char** argv = (const char**) ::malloc(sizeof(char*) * 2);

                if (argv != NULL) {
                    argv[0] = _executable.c_str();
                    argv[1] = NULL;

                    const char** envp = (const char**) ::malloc(sizeof(char*) * (_env.size() + 1));
                    if (envp != NULL) {
                        for (size_t i = 0; i < _env.size(); ++i)
                            envp[i] = ::strdup(_env[i].c_str());
                        envp[_env.size()] = NULL;

                        if (_input_to.enabled()) {
                            safe_dup2(STDIN_FILENO, _input_to.value());
                            webserv::pal::fs::close(_input_to.value());
                        }
                        if (_output_to.enabled()) {
                            safe_dup2(STDOUT_FILENO, _output_to.value());
                            webserv::pal::fs::close(_output_to.value());
                        }

                        ::execve(argv[0], (char *const*) argv, (char *const*) envp);
                    }
                }
                std::cerr << "Execve failed" << std::endl;
                exit(127);
            }

            pid_t fork_task::perform(wait_set& set) {
                // TODO: Fail if executable does NOT exist
                std::pair<fork_status, pid_t> result = fork();

                switch (result.first) {
                    case fork_status_i_am_parent:
                        set.add(result.second);
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

            void fork_task::close_on_fork(int fd) {
                _to_close.push_back(fd);
            }

            void fork_task::add_env(std::string line) {
                _env.push_back(line);
            }

        }
    }
}
