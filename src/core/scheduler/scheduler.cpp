#include "scheduler.hpp"

namespace webserv {
    namespace core {

        scheduler::scheduler(instance& the_inst) : component(the_inst) {

        }

        scheduler::~scheduler() {

        }

        void scheduler::tick() {
            std::vector<webserv::util::state_machine_base*>::iterator it = handlers.begin();

            while (it != handlers.end()) {
                std::cout << "Ticking " << *it << std::endl;
                if ((*it)->is_stopped()) {
                    handlers.erase(it);
                    std::cout << "Removing state machine " << *it << std::endl;
                    delete (*it);
                    break;
                }
                (*it)->tick();
                ++it;
            }
        }

        void scheduler::register_connection(webserv::util::connection* new_connection, webserv::core::routing& routing) {
            handlers.push_back(new webserv::http::http_handler(new_connection, routing));
        }

    }
}
