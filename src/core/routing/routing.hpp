#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/http_response.hpp"
#include "../../http/request.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"

namespace webserv {
    namespace core {

        class   selector;

        class routing : public component {

        public:
            routing(instance& the_inst);
            ~routing();

            webserv::http::http_response* look_up(webserv::http::request_core& request);

            void tick();

        }; // class selector

        class routing_table {
            // TODO: private member "anchor"?
            std::map<std::pair<std::string, std::string> >   prefix_rules;
        
        public:
            routing_table() {}
            ~routing_table() {}

            void add_rule(std::string a, std::string b);
            webserv::http::path query(webserv::http::path oldpath);

        }; // class routing_table

    } // namespace core
} // namespace webserv

#endif
