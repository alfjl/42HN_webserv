#ifndef WEBSERV_UTIL_STATE_MACHINE_HPP
#define WEBSERV_UTIL_STATE_MACHINE_HPP

#include "../defs.hpp"

namespace webserv {
    namespace util {

        class state_machine_base {
        public:
            virtual void tick() = 0;
        };

        template<typename Impl>
        class state_machine : public state_machine_base {
        private:
            typedef void (Impl::*state_function)();

            std::stack<state_function>  return_stack;
            state_function              current_func;
            bool                        yielding;

            void dispatch_end() { end(); }

        public:
            virtual void start() = 0;
            virtual void end() = 0;

            state_machine() {
                next(&state_machine::start);
            }

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

            void stop() {
                while (!return_stack.empty())
                    return_stack.pop();
                next(&state_machine::dispatch_end);
            }

            bool is_yielding() { return yielding; }
            void yield() { yielding = true; }
            void unyield() { yielding = false; }

            void tick() {
                unyield();
                (((Impl*) this)->*current_func)();
            }
        }; // state_machine

    } // namespace util
} // namespace webserve

#endif
