#ifndef WEBSERV_UTIL_COMPONENT_HPP
#define WEBSERV_UTIL_COMPONENT_HPP

namespace webserv {
    namespace util {

        template<typename T>
        class component {
            T& the_inst;

        public:
            component(T& _the_inst) : the_inst(_the_inst) {}
            ~component() {}

            T& get_parent() { return the_inst; }
        };

    }
}

#endif
