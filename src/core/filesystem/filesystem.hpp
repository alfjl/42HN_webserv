#ifndef WEBSERV_CORE_FILESYSTEM_HPP
#define WEBSERV_CORE_FILESYSTEM_HPP

#include "../../defs.hpp"
#include "../component.hpp"
#include "../../http/uri.hpp"

/*
	For later What does the filesystem do?
*/

namespace webserv {
	namespace core {

		class filesystem : public component {
		public:
			filesystem(instance& the_inst);
			~filesystem();

			bool open_absolute(webserv::util::path path, std::ifstream& stream);
			bool open(webserv::util::path path, std::ifstream& stream);

            webserv::util::path read_relative_path(webserv::util::path path);
            webserv::util::path read_absolute_path(webserv::util::path path);
            bool                is_directory(webserv::util::path path);
		
        }; //class filesystem

	} // namespace core
} // namespace webserv

#endif