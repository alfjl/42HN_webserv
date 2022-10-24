#include "../pal/cpp/conv.hpp"
#include "../pal/env/env.hpp"
#include "../pal/cpp/optional.hpp"

#include "../core/routing/all.hpp"

#include "config_parser.hpp"

namespace webserv {
    namespace config {
	
		config_parser::config_parser(webserv::util::iflow& flow, webserv::core::instance& instance) : parser(flow), _instance(instance) {
		}

		static bool is_word_char(char c) {
			return (!isspace(c)) && (c != ';') && (c != '{') && (c != '}');
		}

		std::string config_parser::read_word() {
			std::string word;

			skip_whitespace();
			while (true) {
				char c;
				     if (!this_char(c)) break;
				else if (!is_word_char(c)) break;
				else { word += c; next_char(c); }
			}

			return word;
		}

		webserv::util::path config_parser::read_path() {
			return webserv::util::path(read_word());
		}

		int config_parser::read_int() {
			int result;
			std::string word = read_word();
			if (webserv::pal::cpp::string_to_int(word.c_str(), result)){
				return result;
			}
			return 0;
		}

		void config_parser::skip_whitespace() {
			while (check(' ') || check('\t') || check('\r') || check('\n') || skip_comment());
		}

        bool config_parser::skip_comment() {
            if (check('#')) {
                while (true) {
                    char c;
                         if (!next_char(c)) break;
                    else if (c == '\n') break;
                }
                return true;
            }
            return false;
        }

        bool config_parser::checks(std::string str) {
            skip_whitespace();
            return parser::checks(str);
        }

        void config_parser::expects(std::string str) {
            skip_whitespace();
            parser::expects(str);
        }

		bool config_parser::check_terminator() {
			return checks(";");
		}

		void config_parser::expect_terminator() {
			expects(";");
		}

		bool config_parser::check_path(webserv::util::path& loc) {
			// TODO!
			loc = read_path();
			return true;
		}

		webserv::util::path config_parser::expect_path() {
			webserv::util::path p;
			if (!check_path(p)) parse_error("Expected a path!");
			return p;
		}

		webserv::util::path config_parser::expect_relative_path(webserv::util::path anchor) {
			if (checks("absolute")) return expect_path();
			else return anchor + expect_path();
		}

		void config_parser::parse_listen() {
			while (!check_terminator()){
				_instance.on_port(read_int());
			}
		}

		void config_parser::parse_location(webserv::util::path anchor) {
			webserv::util::path name = expect_path();
			webserv::util::path full_path = anchor + name;
			webserv::util::path resource_path = full_path;
			webserv::util::path resolved_path = full_path;

			bool wildcard = false;
			bool translate = false;
			bool is_redir = false;
			bool is_cgi   = false;
			webserv::pal::cpp::optional<unsigned int> error_code;

			expects("{");
			while (!checks("}")) {
				if (checks("location")) {
					parse_location(full_path);
					continue;
				} else if (checks("reacts")) {
					expects("to");
					expects("all");
					wildcard = true;
				} else if (checks("displays")) {
					if (checks("translated"))
						translate = true;

					if (checks("error_page")) {
						skip_whitespace();
						error_code.enable(expect_uint());
					} else if (checks("redirection")) {
						expects("to");
						resolved_path = expect_path();
					} else if (checks("cgi")) {
						resolved_path = expect_relative_path(full_path);
						is_cgi        = true;
					} else {
						if (checks("files"));
						else expects("file");
					}
				}
				expect_terminator();
			}

			webserv::core::rule*                 rule;
			webserv::core::translation_function* translation;
			webserv::core::route*                route;
			
			if (wildcard) rule = new webserv::core::prefix_rule(resource_path);
			else          rule = new webserv::core::identity_rule(resource_path);

			if (translate) translation = new webserv::core::relative_translation_function();
			else           translation = new webserv::core::zero_translation_function();

			if (error_code.enabled()) route = new webserv::core::error_route(error_code.value());
			else if (is_redir)        route = new webserv::core::redirection_route(resolved_path);
			else if (is_cgi)          route = new webserv::core::cgi_route(resolved_path);
			else                      route = new webserv::core::file_route(resolved_path);

			_instance.get_routing_table().add_rule(rule, translation, route);
		}

		/*
			#x choose port for each server 
			#x choose host for each server
			#x setup server_name or NOT
			# first server for host:port will be default -> answers all requests that don't belong to other servers
			# setup default error pages
			# limit client body size
			# routes with 1 or multiple rules/confguration (routes won't use ragexp)
			# 	define list of accepted http methodes for route
			# 	define http redirection
			# 	define directory or file from where the file should be searched
			# 	turn on or off directory listing
			# 	set default file to answer if request is a directory
			# 	execute cgi for certain file extensions (e.g. .php)
			# 	route able to accept uploaded files & configure where they should be saved
			# make multiple config files to show that everything works
		

			enum http_method translate_http_method(std::string name) {
				     if (name == "GET") return http_method_get;
				else if  ...
				else parse_error("Unknown method: " + name);
			}
		*/
		void config_parser::run() {
            webserv::util::path local_directory(webserv::pal::env::pwd());

			// start
			expects("server");
			expects("{");
			while(!checks("}")){
				if (checks("listen")) {
					parse_listen();
					continue ;
				} else if (checks("client_max_body_size")) {
					std::cout << "Client_max_body_size: " << read_int() << std::endl;
				} else if (checks("error_page")) {
					std::cout << "Error_page: " << read_int();
					std::cout << " " << read_path() << std::endl;
				} else if (checks("cgi_ext")) {
					std::cout << "CGI_ext: " << read_word();
					std::cout << " " << read_path() << std::endl;
				} else if (checks("autoindex")) {
					std::cout << "Autoindex: " << read_word() << std::endl;
					// 	 if (cheks("on")) {}
					// else if (checks("off")) {}
				} else if (checks("index")) {
					std::cout << "Index: " << read_path();
					std::cout << " " << read_word() << std::endl;
				} else if (checks("server_name")) {
					while (!checks(";")){
						std::cout << "Server_name: " << read_word() << std::endl;
					}
					continue ;
				} else if (checks("anchor")) {
                    _instance.set_anchor((local_directory.cd(read_word()).to_absolute_string()));
				} else if (checks("index_page")) {
					std::cout << "Index_page: " << read_word() << std::endl;
				} else if (checks("location")) {
					parse_location(webserv::util::path());
					continue ;
				} 
				expects(";");
			}
			// end
		}
    }
}
