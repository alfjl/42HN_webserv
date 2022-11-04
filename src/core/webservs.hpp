#ifndef WEBSERV_CORE_WEBSERVS_HPP
#define WEBSERV_CORE_WEBSERVS_HPP

#include "../defs.hpp"
#include "instance.hpp"

namespace webserv {
    namespace core {

        class webservs {
            std::vector<instance*>  _instances;
            bool                    _is_running;
        
            void tick();
            bool is_running();

        public:
            webservs();
            ~webservs();

            instance* new_instance();

            bool is_busy();

            void run();

            void interrupt();
        };

    }
}

#endif
