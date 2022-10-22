#ifndef WEBSERVER_UTIL_TRIPLE_HPP
#define WEBSERVER_UTIL_TRIPLE_HPP

#include "../defs.hpp"

namespace webserv {
	namespace util {

        template <typename X, typename Y, typename Z>
		class triple {
        public:
            const X   _first;
            const Y   _second;
            const Z   _third;

            triple(X first, Y second, Z third) : _first(first), _second(second), _third(third) {

            }

            triple(const triple& other) : _first(other._first), _second(other._second), _third(other._third) {
            
            }
		};

	}
}

#endif
