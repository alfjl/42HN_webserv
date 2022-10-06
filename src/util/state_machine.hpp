#ifndef WEBSERV_UTIL_STATE_MACHINE_HPP
#define WEBSERV_UTIL_STATE_MACHINE_HPP

#include "../defs.hpp"

namespace webserv {
    namespace util {

        enum state_machine_status {
            state_machine_status_RUNNING,
            state_machine_status_YIELDING,
            state_machine_status_STOPPED,
        };

        class state_machine_base {
        public:
            virtual void tick() = 0;
            virtual bool is_stopped() = 0;
        };

        template<typename Impl>
        class state_machine : public state_machine_base {
            typedef void (Impl::*state_function)();

            enum state_machine_status   status;
            std::stack<state_function>  return_stack;
            state_function              current_func;

        public:
            virtual void start() = 0;

            state_machine() {
                set_status(state_machine_status_RUNNING);
                next(&state_machine::start);
            }

            enum state_machine_status get_status() { return status; }
            void set_status(enum state_machine_status s) { status = s; }

            bool is_running() { return get_status() == state_machine_status_RUNNING; }
            bool is_yielding() { return get_status() == state_machine_status_YIELDING; }
            bool is_stopped() { return get_status() == state_machine_status_STOPPED; }

            void yield() { set_status(state_machine_status_YIELDING); }
            void unyield() { set_status(state_machine_status_RUNNING); }


            void next(state_function func) {
                current_func = func;
            }

            void later(state_function func) {
                return_stack.push(func);
            }

            void ret() {
                if (return_stack.empty()) {
                    set_status(state_machine_status_STOPPED);
                } else {
                    next(return_stack.top());
                    return_stack.pop();
                }
            }

            void stop() {
                while (!return_stack.empty())
                    return_stack.pop();
                set_status(state_machine_status_STOPPED);
            }

            void tick() {
                unyield();
                while (is_running()) {
                    (((Impl*) this)->*current_func)();
                }
            }
        };

    }
}

#endif
