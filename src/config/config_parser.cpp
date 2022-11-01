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

		void config_parser::parse_location(webserv::util::path anchor, webserv::pal::cpp::optional<bool>& server_autoindex) {
			webserv::util::path name = expect_path();
			webserv::util::path full_path = anchor + name;
			webserv::util::path resource_path = full_path;
			webserv::util::path resolved_path = full_path;

			bool wildcard = false;
			bool translate = false;
			bool is_redir = false;
			bool is_cgi   = false;
			webserv::pal::cpp::optional<unsigned int> error_code;
            webserv::pal::cpp::optional<std::string> executor;
            webserv::pal::cpp::optional<std::string> extension;
            webserv::pal::cpp::optional<std::set<webserv::http::http_method> > allowed_methods;
            webserv::pal::cpp::optional<unsigned int> max_body;
            webserv::pal::cpp::optional<bool>         autoindex;

            std::cout << "INSIDE SERVER.INDEX enabled = " << server_autoindex.enabled() << std::endl;

            if (checks("extension"))
                extension.enable(read_word());

            if (checks("autoindex")) {
                     if (checks("on")) { autoindex.enable(true); }
                else if (checks("off")) { autoindex.enable(false); }
            } else {
                if (server_autoindex.enabled())
                    autoindex.enable(server_autoindex.value());
            }

			expects("{");
			while (!checks("}")) {
				if (checks("location")) {
					parse_location(full_path, autoindex);
					continue;
				} else if (checks("reacts")) {
					expects("to");
					expects("all");
					wildcard = true;
                } else if (checks("methods")) {
                    allowed_methods.enable();
                    while (!check_terminator()) {
                             if (checks("GET") || checks("get")) allowed_methods.value().insert(webserv::http::http_method_get);
                        else if (checks("POST") || checks("post")) allowed_methods.value().insert(webserv::http::http_method_post);
                        else if (checks("PUT") || checks("put")) allowed_methods.value().insert(webserv::http::http_method_put);
                        else if (checks("DELETE") || checks("delete")) allowed_methods.value().insert(webserv::http::http_method_delete);
                        else if (checks("HEAD") || checks("head")) allowed_methods.value().insert(webserv::http::http_method_head);
                        else parse_error("Expected a method!");
                    }
                    continue;
                } else if (checks("maxBody")) {
                    skip_whitespace();
                    max_body.enable(expect_uint());
				} else if (checks("autoindex")) {
					// std::cout << "Autoindex: " << read_word() << std::endl;
						 if (checks("on")) { autoindex.enable(true); }
					else if (checks("off")) { autoindex.enable(false); }
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
                        if (checks("at"))
                            resolved_path = expect_path();
                        else
						    resolved_path = full_path;
						is_cgi        = true;
                        if (checks("using")) {
                            executor.enable(expect_path().to_absolute_string());
                        }
					} else {
						if (checks("files"));
						else expects("file");

                        if (checks("at"))
                            resolved_path = expect_path();
                    }
				}
				expect_terminator();
			}

			webserv::core::rule*                 rule;
			webserv::core::translation_function* translation;
			webserv::core::route*                route;
			
			if (wildcard) rule = new webserv::core::prefix_rule(resource_path);
			else          rule = new webserv::core::identity_rule(resource_path);

            if (extension.enabled())
                rule->set_extension(extension.value());

			if (translate) translation = new webserv::core::relative_translation_function();
			else           translation = new webserv::core::zero_translation_function();

			if (error_code.enabled()) route = new webserv::core::error_route(error_code.value());
			else if (is_redir)        route = new webserv::core::redirection_route(resolved_path);
			else if (is_cgi) {
                webserv::core::cgi_route* cgir = new webserv::core::cgi_route(resolved_path);
                if (executor.enabled())
                    cgir->set_executor(executor.value());
                route = cgir;
            }
			else                      route = new webserv::core::file_route(resolved_path);

            if (allowed_methods.enabled()) {
                route->disable_all_methods();

                std::set<webserv::http::http_method>::const_iterator it = allowed_methods.value().begin();

                while (it != allowed_methods.value().end()) {
                    route->set_allowed_method(*it);
                    ++it;
                }
            }

            if (max_body.enabled())
                route->set_max_body(max_body.value());

            if (autoindex.enabled()) {
                route->set_directory_listing(autoindex.value());
                std::cout << "in autoindex.enabled()" << std::endl;
            } else {
                    std::cout << "in autoindex. NOT enabled()" << std::endl;
                if (server_autoindex.enabled()) {
                    route->set_directory_listing(server_autoindex.value());
                    std::cout << "in server_autoindex. enabled()" << std::endl;
                } else
                    std::cout << "in server_autoindex. NOT enabled()" << std::endl;
            }

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
            webserv::pal::cpp::optional<bool>            _server_autoindex;

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
					// std::cout << "Server Autoindex: " << read_word() << std::endl;
						 if (checks("on")) { _server_autoindex.enable(true); }
					else if (checks("off")) { _server_autoindex.enable(false); }
				} else if (checks("index")) {
					std::cout << "Index: " << read_path();
					std::cout << " " << read_word() << std::endl;
				} else if (checks("server_name")) {
					while (!checks(";")){
                        _instance.set_names(read_word());
					}
					continue ;
				} else if (checks("anchor")) {
                    _instance.set_anchor((local_directory.cd(read_word()).to_absolute_string()));
				} else if (checks("index_page")) {
					std::cout << "Index_page: " << read_word() << std::endl;
				} else if (checks("location")) {
                    // std::cout << "SERVER.INDEX enabled = " << _server_autoindex.enabled() << std::endl;
					parse_location(webserv::util::path(), _server_autoindex);
					continue ;
				} 
				expect_terminator();
			}
			// end
		}
    }
}
