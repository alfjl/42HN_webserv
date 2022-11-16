#include "state_machine.hpp"

namespace webserv {
    namespace util {

		state_machine_base::~state_machine_base() {}

		state_machine::state_machine() : sp(0) {
            set_status(state_machine_status_RUNNING);
            later(&state_machine::start);
        }

		enum state_machine_status state_machine::get_status() { return status; }
		void state_machine::set_status(enum state_machine_status s) { status = s; }

		bool state_machine::is_running() { return get_status() == state_machine_status_RUNNING; }
		bool state_machine::is_yielding() { return get_status() == state_machine_status_YIELDING; }
        bool state_machine::is_sleeping() { return get_status() == state_machine_status_SLEEPING; }
		bool state_machine::is_stopped() { return get_status() == state_machine_status_STOPPED; }

		void state_machine::yield() { set_status(state_machine_status_YIELDING); }
		void state_machine::unyield() { set_status(state_machine_status_RUNNING); }

		void state_machine::fall_asleep() { set_status(state_machine_status_SLEEPING); }
		void state_machine::wake_up() { set_status(state_machine_status_RUNNING); }

        state_machine::state_function state_machine::pop() {
            state_function f = returns[--sp];
            return f;
        }

		void state_machine::stop() {
            sp = 0;
			set_status(state_machine_status_STOPPED);
		}

		void state_machine::tick() {
            unsigned int i = 0;
            if (is_sleeping()) return;
			unyield();
			while (is_running() && i < 16*1024) {
                if (sp == 0) {
                    set_status(state_machine_status_STOPPED);
                    break;
                }
                state_function current_func = pop();
				try
                {
                    (this->*current_func)();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    set_status(state_machine_status_STOPPED);
                }
                i++;
			}
		}

    }
}
