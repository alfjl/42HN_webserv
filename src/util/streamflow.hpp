#ifndef WEBSERVER_UTIL_STREAMFLOW_HPP
#define WEBSERVER_UTIL_STREAMFLOW_HPP

#include "../defs.hpp"

#include "iflow.hpp"

namespace webserv {
	namespace util {

		class streamflow : public iflow {
			std::istream& the_stream;
		public:
			streamflow(std::istream& stream);

			bool has_next();
            bool next_char(char& loc);
		};

		class stringflow : public streamflow {
			std::istringstream stream;
		public:
			stringflow(const std::string& s);
		};

		class fileflow : public streamflow {
			std::ifstream stream;
		public:
			fileflow(const char* path);
		};


	}
}

#endif