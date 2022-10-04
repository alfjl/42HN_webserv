#ifndef WEBSERV_CORE_FILESYSTEM_HPP
#define WEBSERV_CORE_FILESYSTEM_HPP

#include "../../defs.hpp"
#include "../../http/uri.hpp"
#include "../component.hpp"

namespace webserv {
	namespace core {

		class filesystem : public component {
			std::string add_anchor(webserv::util::path path) const;

		public:
			filesystem(instance& the_inst);
			~filesystem();

			bool open_absolute(webserv::util::path path, std::ifstream& stream);
			bool open(webserv::util::path path, std::ifstream& stream);

			bool write_absolute(webserv::util::path path, std::ofstream& stream);
			bool write(webserv::util::path path, std::ofstream& stream);

			bool del_absolute(webserv::util::path path);
			bool del(webserv::util::path path);

            std::vector<webserv::util::path> read_relative_path(webserv::util::path path);
            std::vector<webserv::util::path> read_absolute_path(webserv::util::path path);
            bool                             is_directory(webserv::util::path path);
        };

	}
}

#endif
