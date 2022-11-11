#ifndef WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP
#define WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP

#include "../component.hpp"

#include "../../http/handler/http_handler.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"
#include "../routing/routing.hpp"

namespace webserv {
    namespace http { class cgi_handler; class writing_handler; }
    
    namespace core {

        class scheduler : public instance_component {
        private:
            std::vector<webserv::util::state_machine_base*> handlers;
            std::queue<webserv::util::state_machine_base*> handlers_to_add;
        
        public:
            scheduler(instance& the_inst);
            ~scheduler();

            bool are_tasks_pending();

            void register_connection(webserv::util::connection* new_connection, webserv::core::instance& instance);
            webserv::http::cgi_handler* register_cgi_connection(webserv::util::connection* connection);
            webserv::http::writing_handler* register_writing_connection(std::string message_body, webserv::util::connection* connection);

            void tick();
        };

    }
}

#endif
