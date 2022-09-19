#ifndef WEBSERV_CORE_INSTANCE_HPP
#define WEBSERV_CORE_INSTANCE_HPP

#include "../defs.hpp"

#include "driver/driver.hpp"
#include "scheduler/scheduler.hpp"
#include "../util/connection.hpp" // ALF

namespace webserv {
    namespace core {

        /* ----------- TTT ------------ */
        class driver;
        class scheduler;
        /* ----------- TTT ------------ */

        class instance {

        private:
            driver    _driver;
            scheduler _scheduler;

        public:
            instance();
            ~instance();

            driver&     get_driver()    { return _driver; }
            scheduler&  get_scheduler() { return _scheduler; }
            void        pass_connection(webserv::util::connection* Conny) { // ALF //; spaeter auslagern
                _scheduler.register_connection(Conny); // ALF
            }

            bool is_running() { return true; }

            void run();

        }; // class instance

    } // namespace core
} // namespace webserv

#endif
