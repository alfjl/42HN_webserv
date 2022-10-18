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
            virtual ~state_machine_base() {}
            
            virtual void tick() = 0;
            virtual bool is_stopped() = 0;
        };

        class state_machine : public state_machine_base {
        protected:
            typedef void (state_machine::*state_function)();

            template<typename T>
            state_function conv(T value) {
                return reinterpret_cast<state_function>(value);
            }

        private:
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


            template<typename T>
            void next(T func) {
                current_func = conv(func);
            }

            template<typename T>
            void later(T func) {
                return_stack.push(conv(func));
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
                    (this->*current_func)();
                }
            }
        };

    }
}

#endif
