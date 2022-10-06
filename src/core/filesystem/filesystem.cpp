#include "filesystem.hpp"

#include "../../pal/dir/access.hpp"
#include "../../pal/dir/del.hpp"
#include "../../pal/dir/readdir.hpp"
#include "../../pal/env/env.hpp"

namespace webserv {
	namespace core {

		filesystem::filesystem(instance& the_inst) : component(the_inst){

		}

		filesystem::~filesystem() {

		}

        std::string filesystem::add_anchor(webserv::util::path path) const {
            return "/" + (webserv::pal::env::pwd().cd("../www") + path).get_addr_s();
        }

		bool filesystem::open_absolute(webserv::util::path path, std::ifstream& stream) {
			stream.open(add_anchor(path).c_str());
            std::cout << "Opening /" << path << std::endl;
			return stream.is_open();
		}

		bool filesystem::open(webserv::util::path path, std::ifstream& stream) {
			return open_absolute(path, stream);
		}

        bool filesystem::write_absolute(webserv::util::path path, std::ofstream& stream) {
			stream.open(add_anchor(path).c_str());
            std::cout << "Opening /" << path << std::endl;
			return stream.is_open();
		}

		bool filesystem::write(webserv::util::path path, std::ofstream& stream) {
			return write_absolute(path, stream);
		}

        bool filesystem::del_absolute(webserv::util::path path) {
            // return webserv::pal::dir::rmdir(add_anchor(path).c_str());
            return webserv::pal::dir::remove(add_anchor(path).c_str());
        }

        bool filesystem::del(webserv::util::path path) {
            return del_absolute(path);
        }

        /*
         * Returns a vector of path, for all elements lying under this path
         * Relative path only
         */
        std::vector<webserv::util::path> filesystem::read_relative_path(webserv::util::path path) {
            std::vector<webserv::util::path> v_path;
            std::vector<std::string> files = webserv::pal::dir::read_directory(add_anchor(path));

            for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
                v_path.push_back(webserv::util::path(*it));
            }

            return v_path;
        }

        /*
         * Returns a vector of path, for all elements lying under this path
         * Absolute path
         */
        std::vector<webserv::util::path> filesystem::read_absolute_path(webserv::util::path path) {
            std::vector<webserv::util::path> v_path;
            std::vector<std::string> files = webserv::pal::dir::read_directory(add_anchor(path));

            for (int i = 0; i < files.size(); ++i) {
                v_path.push_back(webserv::util::path(path.get_addr_s()).cd(files[i]));
            }

            return v_path;
        }

        /*
         * Checks if path is a directory
         */
        bool filesystem::is_directory(webserv::util::path path) {
            return webserv::pal::dir::is_directory(add_anchor(path));
        }

        /*
         * Checks if path is accessible
         */
        bool filesystem::accessible(webserv::util::path path) {
            return (webserv::pal::dir::access(path.get_addr_s()));
        }


	}
}