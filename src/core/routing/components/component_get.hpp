#ifndef WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_GET_HPP
#define WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_GET_HPP

#include "component.hpp"

namespace webserv {
    namespace core {

        class routing;

        class routing_component_get : public routing_component {
        public:
            routing_component_get(routing& routing);
        };

    }
}

#endif
