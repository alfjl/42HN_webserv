#ifndef WEBSERVER_UTIL_STREAMFLOW_HPP
#define WEBSERVER_UTIL_STREAMFLOW_HPP

#include "../defs.hpp"

#include "iflow.hpp"

namespace webserv {
	namespace util {

		class streamflow : public iflow {
		public:
			streamflow(std::istream&);
			~streamflow();

			bool has_next();
            bool next_char(char& loc);
		};

		// class stringflow : public streamflow {
		// public: 
		// 	stringflow(std::string&);


		// };

		// class fileflow : public streamflow {
		// public: 
			

		// }:

	}
}

#endif