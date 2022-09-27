#ifndef WEBSERV_CORE_FILESYSTEM_HPP
#define WEBSERV_CORE_FILESYSTEM_HPP

#include "../../defs.hpp"
#include "../component.hpp"

/*
	For later What does the filesystem do?
*/

namespace webserv {
	namespace core {

		class filesystem : public component {
		public:
			filesystem(instance& the_inst);
			~filesystem();

			// fileflow open()

		}; //class filesystem

	} // namespace core
} // namespace webserv

#endif