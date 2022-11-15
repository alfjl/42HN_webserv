#include "../../instance.hpp"

#include "../pages/pages.hpp"

#include "component_pages.hpp"


namespace webserv {
    namespace core {

        routing_component_pages::routing_component_pages(routing& routing) : routing_component(routing) {
            
        }

        void routing_component_pages::error_page(unsigned int code) {
            get_parent().get_request().get_line().get_method() = webserv::http::http_method_get;

            if (get_parent().get_recursion_count() >= 5)
                error_code(get_response(), code);
            else {
                route* the_route = get_parent().get_table().query_error_page(code);
                if (the_route == NULL) {
                    error_code(get_response(), code);
                } else {
                    get_parent().follow_route(the_route);
                }
            }
        }

    }
}
