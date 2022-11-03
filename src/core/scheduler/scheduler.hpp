#ifndef WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP
#define WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP

#include "../component.hpp"

#include "../../http/handler/http_handler.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"
#include "../routing/routing.hpp"

namespace webserv {
    namespace http { class cgi_handler; }
    
    namespace core {

        class scheduler : public component {
        private:
            std::vector<webserv::util::state_machine_base*> handlers;
            std::queue<webserv::util::state_machine_base*> handlers_to_add;
        
        public:
            scheduler(instance& the_inst);
            ~scheduler();

            void register_connection(webserv::util::connection* new_connection, webserv::core::instance& instance);
            webserv::http::cgi_handler* register_cgi_connection(webserv::util::connection* connection);

            void tick();
        };

    }
}

#endif
