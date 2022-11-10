#include "../defs.hpp"

#include "streamflow.hpp"

namespace webserv {
	namespace util {

		streamflow::streamflow(std::istream& stream) : the_stream(stream), last(-1), last_valid(false) {
		}

		void streamflow::refresh() {
			if (!last_valid) {
				last = the_stream.eof() ? -1 : the_stream.get();
				last_valid = true;
			}
		}
	
		bool streamflow::has_next() {
			refresh();
			return (last != -1);
		}

		bool streamflow::next_char(char& loc) {
			refresh();
			loc = last;
			last_valid = false;
			return last != -1;
		}

		bool streamflow::good() {
			return the_stream.good();
		}

		stringflow::stringflow(const std::string& s) : streamflow(stream), stream(s) {
		}

		fileflow::fileflow(const char* path) : streamflow(stream), stream(path) {
		}

	}
}