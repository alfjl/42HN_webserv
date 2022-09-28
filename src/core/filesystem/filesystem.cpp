#include "filesystem.hpp"

namespace webserv {
	namespace core {

		filesystem::filesystem(instance& the_inst) : component(the_inst){

		}

		filesystem::~filesystem() {

		}

		std::ifstream open_absolute(webserv::http::path path) {
			return std::ifstream("/" + path.get_addr_s());
		}

	} // namespace core
} // namespace webserv