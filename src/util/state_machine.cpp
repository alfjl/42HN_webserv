#include "state_machine.hpp"

namespace webserv {
    namespace util {

		state_machine_base::~state_machine_base() {}

		state_machine::state_machine() {
            set_status(state_machine_status_RUNNING);
            later(&state_machine::start);
        }

		enum state_machine_status state_machine::get_status() { return status; }
		void state_machine::set_status(enum state_machine_status s) { status = s; }

		bool state_machine::is_running() { return get_status() == state_machine_status_RUNNING; }
		bool state_machine::is_yielding() { return get_status() == state_machine_status_YIELDING; }
		bool state_machine::is_stopped() { return get_status() == state_machine_status_STOPPED; }

		void state_machine::yield() { set_status(state_machine_status_YIELDING); }
		void state_machine::unyield() { set_status(state_machine_status_RUNNING); }

		void state_machine::fall_asleep() { set_status(state_machine_status_SLEEPING); }
		void state_machine::wake_up() { set_status(state_machine_status_RUNNING); }

		void state_machine::stop() {
			while (!return_stack.empty())
				return_stack.pop();
			set_status(state_machine_status_STOPPED);
		}

		void state_machine::tick() {
			unyield();
			while (is_running()) {
                if (return_stack.empty()) {
                    set_status(state_machine_status_STOPPED);
                    break;
                }
                state_function current_func = return_stack.top();
                return_stack.pop();
				(this->*current_func)();
			}
		}

    }
}
