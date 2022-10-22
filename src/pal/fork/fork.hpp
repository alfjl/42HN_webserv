#ifndef WEBSERV_PAL_FORK_FORK_HPP
#define WEBSERV_PAL_FORK_FORK_HPP

#include "../../defs.hpp"

#include "../../util/optional.hpp"


namespace webserv {
    namespace pal {
        namespace fork {

            // struct easypipe {
            //     int in;
            //     int out;
            // };

            bool safe_pipe(int* pipe_in, int* pipe_out);
            bool safe_dup2(int overridden_fd, int original_fd);

            enum fork_status {
                fork_status_boom,
                fork_status_i_am_parent,
                fork_status_i_am_child
            };

            class wait_set {
                std::set<pid_t> pids;
            public:
                wait_set();
                ~wait_set();

                void add(pid_t pid);
                
                bool wait_for(pid_t pid);
                void wait_for_all();
            };

            class fork_task {
                std::string _executable;
                std::vector<std::string> _env;
                std::vector<int> _to_close;
                webserv::util::optional<int> _input_to;
                webserv::util::optional<int> _output_to;

                void do_child_stuff();

            public:
                fork_task(std::string executable);
                ~fork_task();

                pid_t perform(wait_set& set);

                void input_to(int input);
                void output_to(int output);
                void io_to(int input, int output);

                void close_on_fork(int fd);

                void add_env(std::string line);
            };

        }
    }
}

#endif
