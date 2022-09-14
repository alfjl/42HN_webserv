#ifndef WEBSERV_CORE_INSTANCE_HPP
#define WEBSERV_CORE_INSTANCE_HPP

#include "../defs.hpp"

#include "driver/driver.hpp"
#include "scheduler/scheduler.hpp"

namespace webserv {
    namespace core {

        class instance {
            driver    _driver;
            scheduler _scheduler;

        public:
            instance();
            ~instance();

            driver&    get_driver()    { return _driver; }
            scheduler& get_scheduler() { return _scheduler; }

            bool is_running() { return true; }

            void run();
        };

    }
}

#endif
