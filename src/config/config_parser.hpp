#ifndef WEBSERV_CONFIG_CONFIG_PARSER_HPP
#define WEBSERV_CONFIG_CONFIG_PARSER_HPP


#include "../util/parser.hpp"

namespace webserv {
    namespace config {

		class config_parser : public webserv::util::parser{
		
		public:
			config_parser(webserv::util::iflow& flow);
        };

    }
}

#endif
