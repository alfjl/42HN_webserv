#include "filesystem.hpp"

namespace webserv {
	namespace core {

		filesystem::filesystem(instance& the_inst) : component(the_inst){

		}

		filesystem::~filesystem() {

		}

		bool open_absolute(webserv::http::path path, std::ifstream& stream) {
			stream.open("/" + path.get_addr_s());
			return true;
		}

		bool open(webserv::http::path path, std::ifstream& stream) {
			return open_absolute(path, stream);
		}

	} // namespace core
} // namespace webserv