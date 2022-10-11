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
            handlers.push_back(new webserv::http::cgi_handler(connection));
        }

        void scheduler::tick() {
            std::vector<webserv::util::state_machine_base*>::iterator it = handlers.begin();

            while (it != handlers.end()) {
                if (*it == NULL) // Sometimes working Ghetto-Fix, yo!
                    break ;
                    std::cout << (*it)->is_stopped() << std::endl;
                if ((*it)->is_stopped()) {
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
