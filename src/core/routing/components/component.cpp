#include "component.hpp"

#include "../routing.hpp"

#include "../../../http/handler/http_handler.hpp"


namespace webserv {
    namespace core {

        routing_component::routing_component(routing& routing) : component(routing) {
            
        }

        routing_component::~routing_component() {

        }

        instance& routing_component::get_instance() { return get_parent().get_instance(); }


        webserv::http::http_handler&    routing_component::get_http_handler() { return get_parent().get_http_handler(); }
        webserv::http::request&         routing_component::get_request()      { return get_parent().get_request(); }
        webserv::http::response_fixed&  routing_component::get_response()     { return get_parent().get_response(); }
    }
}
