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
            typedef std::vector<std::pair<webserv::util::path, webserv::util::path> >::iterator       iterator;
            typedef std::vector<std::pair<webserv::util::path, webserv::util::path> >::const_iterator const_iterator;
            
            // TODO: private member "anchor"?
            std::vector<std::pair<webserv::util::path, webserv::util::path> >   prefix_rules;
        
        public:
            routing_table() {}
            ~routing_table() {}

            void add_rule(webserv::util::path in, webserv::util::path out);
            webserv::util::path query(webserv::util::path old_path);

        }; // class routing_table

    } // namespace core
} // namespace webserv

#endif
