#ifndef WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP
#define WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP

#include "../component.hpp"

#include "../../http/handler/http_handler.hpp"
#include "../../util/state_machine.hpp"

namespace webserv {
    namespace core {

        class scheduler : public component {
            std::vector<webserv::util::state_machine*> handlers;
        
        public:
            scheduler(instance& the_inst);
            ~scheduler();

            void tick();
        };
    }
}

#endif
