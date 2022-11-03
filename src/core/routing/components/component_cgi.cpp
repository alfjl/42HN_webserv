#include "../../instance.hpp"

#include "../cgi/cgi.hpp"
#include "../pages/pages.hpp"

#include "component_cgi.hpp"


namespace webserv {
    namespace core {

        routing_component_cgi::routing_component_cgi(routing& routing) : routing_component(routing) {
            
        }

        void routing_component_cgi::handle_cgi(route& route) {
            (void) route;  // TODO
        }

    }
}
