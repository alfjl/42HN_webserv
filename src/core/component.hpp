#ifndef WEBSERV_CORE_COMPONENT_HPP
#define WEBSERV_CORE_COMPONENT_HPP

#include "../defs.hpp"
#include "../util/component.hpp"

namespace webserv {
    namespace core {

        class instance;

        class instance_component : public webserv::util::component<instance> {
        public:
            instance_component(instance& the_instance);

            instance& get_instance();
        };
    }
}

#endif
