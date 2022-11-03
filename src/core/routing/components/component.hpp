#ifndef WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_HPP
#define WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_HPP

#include "../../../defs.hpp"
#include "../../../util/component.hpp"

#include "../../../http/proto/response.hpp"

namespace webserv {
    namespace core {

        class routing;
        class instance;

        class routing_component : public webserv::util::component<routing> {
        public:
            routing_component(routing& routing);
            ~routing_component();

            instance& get_instance();

            webserv::http::response_fixed& get_response();

        };

    }
}

#endif
