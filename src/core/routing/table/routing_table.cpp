#include "routing_table.hpp"

namespace webserv {
    namespace core {

        routing_table::routing_table() {
            // default_route = new error_route(418);
            default_route = new error_route(200); // TODO: delete! test only!
        }

        routing_table::~routing_table(){
            iterator it = prefix_rules.begin();
            iterator ite = prefix_rules.end();

            for (; it != ite; ++it) {
                delete it->_first;
                delete it->_second;
                delete it->_third;
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

        /*
         * Checks if prefix of path is included in prefix_rules
         * If yes, returns the correct route
         * according to the specific rule set
         */
        route* routing_table::query(webserv::util::path path) {

            // look_up if prefix substitution rule for path exist
            // and return it, if found
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

    }
}