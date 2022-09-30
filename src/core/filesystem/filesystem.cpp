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

        bool filesystem::write_absolute(webserv::util::path path, std::ofstream& stream) {
			stream.open("/" + path.get_addr_s());
            std::cout << "Opening /" << path << std::endl;
			return stream.is_open();
		}

		bool filesystem::write(webserv::util::path path, std::ofstream& stream) {
			return write_absolute(path, stream);
		}

        /*
         * Returns a vector of path, for all elements lying under this path
         * Relative path only
         */
        std::vector<webserv::util::path> filesystem::read_relative_path(webserv::util::path path)
        {
            std::vector<webserv::util::path> v_path;
            std::vector<std::string> files = webserv::pal::dir::read_directory("/" + path.get_addr_s());

            for (int i = 0; i < files.size(); ++i) {
                v_path.push_back(webserv::util::path(files[i]));
            }

            return v_path;
        }

        /*
         * Returns a vector of path, for all elements lying under this path
         * Absolute path
         */
        std::vector<webserv::util::path> filesystem::read_absolute_path(webserv::util::path path)
        {
            std::vector<webserv::util::path> v_path;
            std::vector<std::string> files = webserv::pal::dir::read_directory("/" + path.get_addr_s());

            for (int i = 0; i < files.size(); ++i) {
                v_path.push_back(webserv::util::path(path.get_addr_s()).cd(files[i]));
            }

            return v_path;
        }

        /*
         * Checks if path is a directory
         */
        bool filesystem::is_directory(webserv::util::path path)
        {
            return webserv::pal::dir::is_directory("/" + path.get_addr_s());
        }

	} // namespace core
} // namespace webserv