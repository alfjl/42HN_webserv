#ifndef WEBSERV_CORE_COMPONENT_HPP
#define WEBSERV_CORE_COMPONENT_HPP


namespace webserv {
    namespace core {

        class instance;

        class component {
            instance& the_inst;

        public:
            component(instance& _the_inst);
            ~component();

            instance& get_instance() { return the_inst; }

        }; // class component

    } // namespace core
} // namespace webserv

#endif
