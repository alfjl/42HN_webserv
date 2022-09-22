#include "../defs.hpp"

#include "streamflow.hpp"

namespace webserv {
	namespace util {

		streamflow::streamflow(std::istream& stream) : the_stream(stream){
		}
	
		bool streamflow::has_next() {
			return (!the_stream.eof());
		}

		bool streamflow::next_char(char& loc) {
			if (has_next()) {
				loc = the_stream.get();// was aus the_stream kommt & nur wenn er auch daten hat
				return true;
			}
			return false;
		}

		stringflow::stringflow(const std::string& s) : streamflow(stream), stream(s) {
		}

		fileflow::fileflow(std::string s) : streamflow(stream), stream(s) {
		}

	}
}