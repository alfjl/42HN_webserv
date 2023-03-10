#ifndef WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_HTTP_HPP
#define WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_HTTP_HPP

#include "component.hpp"

#include "../table/route.hpp"

namespace webserv {
    namespace core {

        class routing;

        class routing_component_http : public routing_component {
        private:
            void process_post_body(webserv::util::path file_path);

        public:
            routing_component_http(routing& routing);

            void handle_head(route& route);
            void handle_get(route& route);
            void handle_post(route& route);
            void handle_delete(route& route);
        };

    }
}

#endif
