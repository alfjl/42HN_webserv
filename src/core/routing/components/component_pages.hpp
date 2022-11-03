#ifndef WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_PAGES_HPP
#define WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_PAGES_HPP

#include "component.hpp"

#include "../table/route.hpp"

namespace webserv {
    namespace core {

        class routing;

        class routing_component_pages : public routing_component {
        public:
            routing_component_pages(routing& routing);

            void error_page(unsigned int code);
        };

    }
}

#endif
