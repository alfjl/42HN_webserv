#ifndef WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP

#include "../../util/path.hpp"

#include "route.hpp"
#include "rule.hpp"

namespace webserv {
    namespace core {

        class routing_table {
            typedef std::vector<std::pair<webserv::util::path, webserv::util::path> >::iterator       iterator;
            typedef std::vector<std::pair<webserv::util::path, webserv::util::path> >::const_iterator const_iterator;
            
            std::vector<std::pair<webserv::core::basic_rule*, webserv::core::route*> >   prefix_rules;
        
        public:
            routing_table() {}
            ~routing_table();

            void add_rule(webserv::core::basic_rule* in, webserv::core::route* out);
            route* query(webserv::util::path path);
        };

    }
}

#endif
