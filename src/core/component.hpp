#ifndef WEBSERV_CORE_COMPONENT_HPP
#define WEBSERV_CORE_COMPONENT_HPP

#include "../defs.hpp"
#include "../util/component.hpp"

namespace webserv {
    namespace core {

        class instance;

        typedef webserv::util::component<instance> component;

    }
}

#endif
