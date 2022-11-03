#include "../../http/handler/cgi_handler.hpp"

#include "scheduler.hpp"


namespace webserv {
    namespace core {

        scheduler::scheduler(instance& the_inst) : instance_component(the_inst) {

        }

        scheduler::~scheduler() {

        }

        bool scheduler::are_tasks_pending() {
            return !(handlers.empty() && handlers_to_add.empty());
        }

        void scheduler::register_connection(webserv::util::connection* new_connection, webserv::core::instance& instance) {
            webserv::http::http_handler* handler = new webserv::http::http_handler(new_connection, instance);
            handlers.push_back(handler);
            handler->increment_refcount();
        }

        webserv::http::cgi_handler* scheduler::register_cgi_connection(webserv::util::connection* connection) {
            webserv::http::cgi_handler* handler = new webserv::http::cgi_handler(connection);
            handlers_to_add.push(handler);
            handler->increment_refcount();
            return handler;
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
                    machine->decrement_refcount();
                    break;
                }
                (*it)->tick();
                ++it;
            }
        }

    }
}
