#include "../../http/handler/cgi_handler.hpp"

#include "scheduler.hpp"


namespace webserv {
    namespace core {

        scheduler::scheduler(instance& the_inst) : component(the_inst) {

        }

        scheduler::~scheduler() {

        }

        void scheduler::register_connection(webserv::util::connection* new_connection, webserv::core::routing& routing) {
            handlers.push_back(new webserv::http::http_handler(new_connection, routing));
        }

        void scheduler::register_cgi_connection(webserv::util::connection* connection) {
            handlers_to_add.push(new webserv::http::cgi_handler(connection, NULL));
        }

        void scheduler::tick() {
            while (!handlers_to_add.empty()) {
                handlers.push_back(handlers_to_add.front());
                handlers_to_add.pop();
            }
            
            std::vector<webserv::util::state_machine_base*>::iterator it = handlers.begin();

            while (it != handlers.end()) {
                if ((*it)->is_stopped()) {
                    // TODO: Add to list of stopped handlers, remove elements later
                    webserv::util::state_machine_base* machine = *it;
                    handlers.erase(it);
                    delete machine;
                    break;
                }
                (*it)->tick();
                ++it;
            }
        }

    }
}
