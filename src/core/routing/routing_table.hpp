#ifndef WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP

#include "../../util/path.hpp"
#include "../../util/triple.hpp"

#include "route/route.hpp"
#include "route/rule.hpp"
#include "route/translation_function.hpp"

namespace webserv {
    namespace core {

        class routing_table {
            typedef std::vector<webserv::util::triple<webserv::core::basic_rule*, webserv::core::translation_function*, webserv::core::route*> >::iterator       iterator;
            typedef std::vector<webserv::util::triple<webserv::core::basic_rule*, webserv::core::translation_function*, webserv::core::route*> >::const_iterator const_iterator;

            std::vector<webserv::util::triple<webserv::core::basic_rule*, webserv::core::translation_function*, webserv::core::route*> >   prefix_rules;

            route* default_route;
        
        public:
            routing_table();
            ~routing_table();

            void add_rule(basic_rule* in, translation_function* rule, route* out);
            void add_rule(basic_rule* in, route* out);

            route* query(webserv::util::path path);
        };

    }
}

#endif
