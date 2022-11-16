#include "component.hpp"

namespace webserv {
    namespace core {

        instance_component::instance_component(instance& the_instance) : component(the_instance) {}

        instance& instance_component::get_instance() { return get_parent(); }

    }
}
