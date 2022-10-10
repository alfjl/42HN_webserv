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

			skip_spaces();
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

		void config_parser::run() {
			// start
			skip_spaces();
			expects("server");
			skip_spaces();
			expects("{");
			while(!checks("}")){
			
				if (checks("listen")) {
					skip_spaces();
					read_int();
				} else if (checks("server_name") || checks("access_log")) {
					while (!checks(";")){
						read_word();
					}
				} else if (checks("root")) {
					read_word();
				} else if (checks("location")) {
					skip_spaces();
					read_path();
					skip_spaces();
					expects("{");
					skip_spaces();
					while (!checks("}")){
						if (checks("root")){
							read_word();
						} else if (checks("proxy_pass")){
							read_word();
						} else if (checks("fastcgi_pass")){
							read_word();
						}
					}
					continue ;
				}
				expects(";");
			}
			// end
		}
    }
}
