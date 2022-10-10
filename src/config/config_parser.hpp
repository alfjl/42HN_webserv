#ifndef WEBSERV_CONFIG_CONFIG_PARSER_HPP
#define WEBSERV_CONFIG_CONFIG_PARSER_HPP

#include "../defs.hpp"

#include "../core/instance.hpp"
#include "../util/parser.hpp"

namespace webserv {
    namespace config {

		class config_parser : public webserv::util::parser {
			webserv::core::instance& _instance;

		protected:
			webserv::util::path read_path();
			std::string read_word();
			int read_int();

		public:
			config_parser(webserv::util::iflow& flow, webserv::core::instance& instance);

			void run();
		};

    }
}

#endif
