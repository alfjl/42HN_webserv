#ifndef WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP
#define WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP

#include "../component.hpp"

#include "../../http/handler/http_handler.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"
#include "../routing/routing.hpp"

namespace webserv {
    namespace core {

        class scheduler : public component {
        private:
            std::vector<webserv::util::state_machine_base*> handlers;
        
        public:
            scheduler(instance& the_inst);
            ~scheduler();

            void tick();
            void register_connection(webserv::util::connection* new_connection, webserv::core::routing& routing);
        };

    }
}

#endif
