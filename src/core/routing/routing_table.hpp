#ifndef WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP

#include "../../util/path.hpp"

namespace webserv {
    namespace core {

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
