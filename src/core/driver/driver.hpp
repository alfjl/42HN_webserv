#ifndef WEBSERV_CORE_DRIVER_DRIVER_HPP
#define WEBSERV_CORE_DRIVER_DRIVER_HPP

#include "../component.hpp"

namespace webserv {
    namespace core {

        class driver : public component {
        public:
            driver(webserv& the_serv);
            ~driver();
        };
    }
}

#endif
