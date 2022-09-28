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

			bool open_absolute(webserv::http::path path, std::ifstream& stream);
			bool open(webserv::http::path path, std::ifstream& stream);

		}; //class filesystem

	} // namespace core
} // namespace webserv

#endif