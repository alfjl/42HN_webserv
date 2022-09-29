#include "filesystem.hpp"
#include "../../pal/dir/readdir.hpp"

namespace webserv {
	namespace core {

		filesystem::filesystem(instance& the_inst) : component(the_inst){

		}

		filesystem::~filesystem() {

		}

		bool filesystem::open_absolute(webserv::util::path path, std::ifstream& stream) {
			stream.open("/" + path.get_addr_s());
            std::cout << "Opening /" << path << std::endl;
			return stream.is_open();
		}

		bool filesystem::open(webserv::util::path path, std::ifstream& stream) {
			return open_absolute(path, stream);
		}

        webserv::util::path filesystem::read_relative_path(webserv::util::path path)
        {

        }

        webserv::util::path filesystem::read_absolute_path(webserv::util::path path)
        {

        }

        bool filesystem::is_directory(webserv::util::path path)
        {
            return webserv::pal::dir::is_directory(path.get_addr_s());
        }

	} // namespace core
} // namespace webserv