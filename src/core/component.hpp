#ifndef WEBSERV_CORE_COMPONENT_HPP
#define WEBSERV_CORE_COMPONENT_HPP

namespace webserv {
    namespace core {
        class webserv;
        class driver;

        class component {
            webserv& the_serv;

        public:
            component(webserv& _the_serv);
            ~component();

            webserv& get_server() { return the_serv; }
        };
    }
}

#endif
