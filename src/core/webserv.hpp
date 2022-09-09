#ifndef WEBSERV_CORE_WEBSERV_HPP
#define WEBSERV_CORE_WEBSERV_HPP

#include "../defs.hpp"
#include "driver/driver.hpp"

namespace webserv {
    namespace core {

        class webserv {
            driver _driver;

        public:
            webserv();
            ~webserv();

            driver& get_driver() { return _driver; }
        };

    }
}

#endif
