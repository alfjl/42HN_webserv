#ifndef WEBSERV_UTIL_STATE_MACHINE_HPP
#define WEBSERV_UTIL_STATE_MACHINE_HPP

#include "../defs.hpp"

namespace webserv {
    namespace util {

        enum state_machine_status {
            state_machine_status_RUNNING,
            state_machine_status_YIELDING,
            state_machine_status_SLEEPING,
            state_machine_status_STOPPED,
        };

        class state_machine_base : public webserv::util::refcounted {
        public:
            virtual ~state_machine_base();
            
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

        public:
            virtual void start() = 0;

            state_machine();

            enum state_machine_status get_status();
            void set_status(enum state_machine_status s);

            bool is_running();
            bool is_yielding();
            bool is_sleeping();
            bool is_stopped();

            void yield();
            void unyield();

            void fall_asleep();
            void wake_up();

            template<typename T>
            void later(T func) {
                return_stack.push(conv(func));
            }

            void stop();
            void tick();
        };

    }
}

#endif
