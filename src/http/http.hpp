#ifndef WEBSERV_HTTP_HTTP_HPP
#define WEBSERV_HTTP_HTTP_HPP

#include "../util/path.hpp"

namespace webserv {
    namespace http {

		std::string find_mime(std::string extension);
		
		const char* code2str(unsigned int code);

    }
}

#endif