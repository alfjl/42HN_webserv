#include "routing_table.hpp"

namespace webserv {
    namespace core {

        /*
         * Checks if 'in' is already in prefix_rules
         * If yes, only changes the second rule to 'out'
         * If not, adds the whole pair<in, out> to prefix_rules
         */
        void routing_table::add_rule(webserv::util::path in, webserv::util::path out) {
            iterator it = prefix_rules.begin();
            iterator ite = prefix_rules.end();

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
         * Checks if prefix of old_path is included in prefix_rules
         * If yes, substitutes the prefix of old_path
         * according to the specific rule set
         */
        route routing_table::query(webserv::util::path old_path) {
            webserv::util::path queried_path(old_path);

            // look_up if prefix substitution rule for old_path exist
            // and substitute it, if found
            const_iterator it = prefix_rules.begin();
            const_iterator ite = prefix_rules.end();
            for (; it != ite; ++it) {
                if (old_path.begins_with(it->first)) {
                    // change prefix of old_path, according to prefix rule
                    // and save in queried_path
                    queried_path = old_path.adapt_prefix(it->first, it->second);
                    break;
                }
            }

            /*
             * For now, just return a new route.
             * We do need to do lookups soon, though.
             *                       - nijakow
             */
            return route(queried_path);
        }

    }
}
