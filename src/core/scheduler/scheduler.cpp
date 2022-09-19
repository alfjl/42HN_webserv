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

        void scheduler::register_connection(webserv::util::connection* Conny) {
            handlers.push_back(new webserv::http::http_handler(Conny));
        }

    } // namespace core
} // namespace webserv
