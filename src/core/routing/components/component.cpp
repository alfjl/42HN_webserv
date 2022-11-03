#include "component.hpp"

#include "../routing.hpp"

namespace webserv {
    namespace core {

        routing_component::routing_component(routing& routing) : component(routing) {
            
        }

        routing_component::~routing_component() {

        }

        instance& routing_component::get_instance() { return get_parent().get_instance(); }

        webserv::http::response_fixed& routing_component::get_response() { return get_parent().get_response(); }

    }
}
