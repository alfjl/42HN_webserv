#include "../pal/cpp/conv.hpp"

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
            return parser::checks(str);
        }

        void config_parser::expects(std::string str) {
            parser::expects(str);
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
			// start
			skip_whitespace();
			expects("server");
			skip_whitespace();
			expects("{");
			skip_whitespace();
			while(!checks("}")){
				skip_whitespace();
				if (checks("listen")) {
					while (!checks(";")){
					skip_whitespace();
					std::cout << "Listen: " << read_int() << std::endl;
					}
					skip_whitespace();
					continue ;
				} else if (checks("client_max_body_size")) {
					skip_whitespace();
					std::cout << "Client_max_body_size: " << read_int() << std::endl;
					skip_whitespace();
				} else if (checks("error_page")) {
					skip_whitespace();
					std::cout << "Error_page: " << read_int();
					skip_whitespace();
					std::cout << " " << read_path() << std::endl;
					skip_whitespace();
				} else if (checks("cgi_ext")) {
					skip_whitespace();
					std::cout << "CGI_ext: " << read_word();
					skip_whitespace();
					std::cout << " " << read_path() << std::endl;
					skip_whitespace();
				} else if (checks("autoindex")) {
					skip_whitespace();
					std::cout << "Autoindex: " << read_word() << std::endl;
					// 	 if (cheks("on")) {}
					// else if (checks("off")) {}
					skip_whitespace();
				} else if (checks("index")) {
					skip_whitespace();
					std::cout << "Index: " << read_path();
					skip_whitespace();
					std::cout << " " << read_word() << std::endl;
					skip_whitespace();
				} else if (checks("server_name")) {
					while (!checks(";")){
						std::cout << "Server_name: " << read_word() << std::endl;
					}
					skip_whitespace();
					continue ;
				} else if (checks("root")) {
					std::cout << "Root: " << read_word() << std::endl;
				} else if (checks("index_page")) {
					std::cout << "Index_page: " << read_word() << std::endl;
				} else if (checks("location")) {
					// if (checks("*.")){

					// } else /* if (checks("/")) */ {

					// }
					skip_whitespace();
					std::cout << "location: " << read_path() << std::endl;
					skip_whitespace();
					expects("{");
					skip_whitespace();
					while (!checks("}")){
						if (checks("root")){
							std::cout << "Location-Root: " << read_word() << std::endl;
						} else if (checks("method")){
							while (!checks(";")){
								std::cout << "Method: " << read_word() << std::endl;
							}
							skip_whitespace();
							continue ;
						} else if (checks("index_page")){
							std::cout << "Location-Index_page: " << read_word() << std::endl;
						}
						skip_whitespace();
						expects(";");
						skip_whitespace();
					}
					skip_whitespace();
					continue ;
				} 
				skip_whitespace();
				expects(";");
				skip_whitespace();
			}
			// end
		}
    }
}
