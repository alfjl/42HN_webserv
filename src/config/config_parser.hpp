#ifndef WEBSERV_CONFIG_CONFIG_PARSER_HPP
#define WEBSERV_CONFIG_CONFIG_PARSER_HPP

#include "../defs.hpp"

#include "../core/webservs.hpp"
#include "../core/instance.hpp"
#include "../util/parser.hpp"
#include "../util/path.hpp"

namespace webserv {
    namespace config {

		class config_parser : public webserv::util::parser {
			webserv::core::webservs& _webservs;
			webserv::core::instance* _instance;
			std::vector<int>         _ports;

		protected:
			void skip_whitespace();
            bool skip_comment();

			webserv::util::path read_path();
			std::string read_word();
			int read_int();

            bool checks(std::string str);
            void expects(std::string str);

			bool check_terminator();
			void expect_terminator();

			bool check_path(webserv::util::path& loc);
			webserv::util::path expect_path();
			webserv::util::path expect_relative_path(webserv::util::path anchor);

			void parse_listen();
			void parse_location(webserv::util::path anchor);

			void run_instance(webserv::util::path local_directory);

			void instance_on_port(webserv::core::instance* inst, int port);

		public:
			config_parser(webserv::util::iflow& flow, webserv::core::webservs& webservs);
			void run();
		};

    }
}

#endif
