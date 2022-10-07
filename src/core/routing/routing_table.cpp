#include "routing_table.hpp"

namespace webserv {
    namespace core {

        /*
         * Checks if 'in' is already in prefix_rules
         * If yes, only changes the second rule to 'out'
         * If not, adds the whole pair<in, out> to prefix_rules
         */
        void routing_table::add_rule(webserv::core::basic_rule* in, webserv::core::route* out) {
            std::vector<std::pair<webserv::core::basic_rule*, webserv::core::route*> >::iterator it = prefix_rules.begin();
            std::vector<std::pair<webserv::core::basic_rule*, webserv::core::route*> >::iterator ite = prefix_rules.end();

            for (; it != ite; ++it) {
                if (it->first == in)
                    break;
            }
            if (it != ite) {
                it->second = out;
            } else {
                prefix_rules.push_back(std::make_pair(in, out));
            }
        }

        /*
         * Checks if prefix of path is included in prefix_rules
         * If yes, returns the correct route
         * according to the specific rule set
         */
        route routing_table::query(webserv::util::path path) {

            // look_up if prefix substitution rule for path exist
            // and return it, if found
            std::vector<std::pair<webserv::core::basic_rule*, webserv::core::route*> >::const_iterator it = prefix_rules.begin();
            std::vector<std::pair<webserv::core::basic_rule*, webserv::core::route*> >::const_iterator ite = prefix_rules.end();
            for (; it != ite; ++it) {
                if (it->first->matches(path)){
                    return *it->second;
                }
            }

            /*
             * For now, just return a new route.
             * We do need to do lookups soon, though.
             *                       - nijakow
             */
            return route(path);
        }

    }
}
