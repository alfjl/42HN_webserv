#ifndef WEBSERV_CORE_INSTANCE_HPP
#define WEBSERV_CORE_INSTANCE_HPP

#include "../defs.hpp"
#include "driver/driver.hpp"

namespace webserv {
    namespace core {

        class instance {
            driver _driver;

        public:
            instance();
            ~instance();

            driver& get_driver() { return _driver; }

            bool is_running() { return true; }

            void run();
        };

    }
}

#endif
