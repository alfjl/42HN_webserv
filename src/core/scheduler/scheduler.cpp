#include "scheduler.hpp"

namespace webserv {
    namespace core {

        scheduler::scheduler(instance& the_inst) : component(the_inst) {

        }

        scheduler::~scheduler() {

        }

        void scheduler::tick() {
            std::vector<webserv::util::state_machine*>::iterator it = handlers.begin();

            while (it != handlers.end()) {
                (*it)->tick();
                ++it;
            }
        }

    } // namespace core
} // namespace webserv
