#include "routing_table.hpp"

namespace webserv {
    namespace core {

        routing_table::routing_table() {
            default_route = new error_route(418);
        }

        routing_table::~routing_table(){
            iterator it = prefix_rules.begin();
            iterator ite = prefix_rules.end();

            for (; it != ite; ++it) {
                delete it->_first;
                delete it->_second;
                delete it->_third;
            }

            for (std::map<unsigned int, route*>::const_iterator it = default_error_pages.begin(); it != default_error_pages.end(); ++it) {
                delete it->second;
            }

            delete default_route;
        }

        /*
         * Checks if 'in' is already in prefix_rules
         * If yes, only changes the second rule to 'out'
         * If not, adds the whole pair<in, out> to prefix_rules
         */
        void routing_table::add_rule(webserv::core::rule* in, webserv::core::translation_function* translate, webserv::core::route* out) {
            prefix_rules.push_back(webserv::util::triple<webserv::core::rule*, webserv::core::translation_function*, webserv::core::route*>(in, translate, out));
        }

        void routing_table::add_rule(rule* in, route* out) {
            add_rule(in, new zero_translation_function(), out);
        }

        void routing_table::add_default_error_page(unsigned int code, route* out) {
            // TODO, FIXME, XXX: This can lead to leaks
            default_error_pages[code] = out;
        }

        /*
         * Checks if prefix of path is included in prefix_rules
         * If yes, returns the correct route
         * according to the specific rule set
         */
        route* routing_table::query(webserv::util::path path) {
            const_iterator it = prefix_rules.begin();
            const_iterator ite = prefix_rules.end();
            for (; it != ite; ++it) {
                match_info meta;
                if (it->_first->matches(path, meta)) {
                    if (!it->_second->convert(meta))
                        continue ;
                    return it->_third->build(meta);
                }
            }

            /*
             * No route found, return the default route.
             */
            {
                match_info meta;
                meta.wildcard_path = path;
                return default_route->build(meta);
            }
        }

        route* routing_table::query_error_page(unsigned int code) {
            match_info info;

            std::map<unsigned int, route*>::const_iterator it = default_error_pages.find(code);
            if (it != default_error_pages.end()) return it->second->build(info);
            else return NULL;
        }

    }
}
