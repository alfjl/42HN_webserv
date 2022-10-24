#ifndef WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_TABLE_HPP

#include "../../../util/path.hpp"
#include "../../../util/triple.hpp"

#include "route.hpp"
#include "rule.hpp"
#include "translation_function.hpp"

namespace webserv {
    namespace core {

        class routing_table {
            typedef std::vector<webserv::util::triple<webserv::core::rule*, webserv::core::translation_function*, webserv::core::route*> >::iterator       iterator;
            typedef std::vector<webserv::util::triple<webserv::core::rule*, webserv::core::translation_function*, webserv::core::route*> >::const_iterator const_iterator;

            std::vector<webserv::util::triple<webserv::core::rule*, webserv::core::translation_function*, webserv::core::route*> >   prefix_rules;
            std::map<unsigned int, route*>  default_error_pages;

            route* default_route;
        
        public:
            routing_table();
            ~routing_table();

            void add_rule(rule* in, translation_function* rule, route* out);
            void add_rule(rule* in, route* out);

            void add_default_error_page(unsigned int code, route* out);

            route* query(webserv::util::path path);
            route* query_error_page(unsigned int code);
        };

    }
}

#endif
