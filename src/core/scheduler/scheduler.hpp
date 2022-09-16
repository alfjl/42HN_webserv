#ifndef WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP
#define WEBSERV_CORE_SCHEDULER_SCHEDULER_HPP

#include "../component.hpp"
#include "../instance.hpp"

#include "../../http/handler/http_handler.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace core {

        class scheduler : public component {
            std::vector<webserv::util::state_machine*> handlers;
        
        public:
            scheduler(instance& the_inst);
            ~scheduler();

            void tick();
            void register_connection(/*reactor/connection*/ webserv::util::connection* Conny) {  // ALF //; spaeter auslagern
                // int index = 0; // how get correct index?
                handlers.push_back(new webserv::http::http_handler(Conny));
            }

        }; // class scheduler

    } // namespace core
} // namespace webserv

#endif
