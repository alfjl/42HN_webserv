#ifndef WEBSERV_CORE_WEBSERVS_HPP
#define WEBSERV_CORE_WEBSERVS_HPP

#include "../defs.hpp"
#include "instance.hpp"
#include "driver/driver.hpp"

namespace webserv {
    namespace core {

        class webservs {
            driver                  _driver;
            std::vector<instance*>  _instances;
            bool                    _is_running;
        
            void tick();

        public:
            webservs();
            ~webservs();

            driver& get_driver();

            instance* new_instance();

            bool is_running();
            bool is_busy();

            void run();

            void interrupt();
        };

    }
}

#endif
