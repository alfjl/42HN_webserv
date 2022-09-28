#include "filesystem.hpp"

namespace webserv {
	namespace core {

		filesystem::filesystem(instance& the_inst) : component(the_inst){

		}

		filesystem::~filesystem() {

		}

		bool filesystem::open_absolute(webserv::http::path path, std::ifstream& stream) {
			stream.open("/" + path.get_addr_s());
            std::cout << "Opening /" << path << std::endl;
			return true;
		}

		bool filesystem::open(webserv::http::path path, std::ifstream& stream) {
			return open_absolute(path, stream);
		}

	} // namespace core
} // namespace webserv