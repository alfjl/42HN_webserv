#include "../../instance.hpp"

#include "../pages/pages.hpp"

#include "component_pages.hpp"


namespace webserv {
    namespace core {

        routing_component_pages::routing_component_pages(routing& routing) : routing_component(routing) {
            
        }

        void routing_component_pages::error_page(unsigned int code) {
            // TODO, FIXME, XXX: Watch out for recursion!
            route* the_route = get_parent().get_table().query_error_page(code);
            if (the_route == NULL) {
                error_code(get_response(), code);
                get_response().write(*get_http_handler().get_connection());
            } else {
                get_parent().follow_route(the_route);
            }
        }

    }
}
