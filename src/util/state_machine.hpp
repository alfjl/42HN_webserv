#ifndef WEBSERV_UTIL_STATE_MACHINE_HPP
#define WEBSERV_UTIL_STATE_MACHINE_HPP

#include "../defs.hpp"

namespace webserv {
    namespace util {

    class state_machine {
    private:
        typedef void (state_machine::*state_function)();

        std::stack<state_function>  return_stack;
        state_function              current_func;
        bool                        yielding;
    
    public:
        virtual void start() = 0;
        virtual void end() = 0;

        state_machine() {}

        void next(state_function func) {
            current_func = func;
        }

        void later(state_function func) {
            return_stack.push(func);
        }

        void ret() {
            if (return_stack.empty()) {
                end();
            } else {
                next(return_stack.top());
                return_stack.pop();
            }
        }

        bool is_yielding() { return yielding; }
        void yield() { yielding = true; }
        void unyield() { yielding = false; }

        void tick() {
            unyield();
            (this->*current_func)();
        }
    }; // state_machine

    } // namespace util
} // namespace webserve

#endif
