#ifndef WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_CGI_HPP
#define WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_CGI_HPP

#include "component.hpp"

#include "../table/route.hpp"

namespace webserv {
    namespace core {

        class routing;

        class routing_component_cgi : public routing_component {
        public:
            routing_component_cgi(routing& routing);

            void handle_cgi(cgi_route& route);
        };

    }
}

#endif
