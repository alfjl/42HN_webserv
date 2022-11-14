#ifndef WEBSERV_CORE_ROUTING_PAGES_PAGES_HPP
#define WEBSERV_CORE_ROUTING_PAGES_PAGES_HPP

#include "../../../http/proto/response.hpp"

namespace webserv {
    namespace core {

		void error_code(webserv::http::response_fixed& response, unsigned int code);
		void permanent_redirect_301(webserv::http::response_fixed& response, webserv::util::path path);
		void temporary_redirect_302(webserv::http::response_fixed& response, webserv::util::path path);
		void internal_server_error_500(webserv::http::response_fixed& response);

		void head_start(std::ostringstream& ost, std::string s);
		void header_one(std::ostringstream& ost, std::string s);
		void header_three(std::ostringstream& ost, std::string s);
		void blockquote(std::ostringstream& ost, std::pair<std::string, std::string> quote);
		void set_delete_response(webserv::http::response_fixed& response);
		void directory_listing(webserv::http::response_fixed& response, std::vector<webserv::util::path> paths);
		void file_listing(webserv::http::response_fixed& response, webserv::util::path file_path, std::ifstream& stream);

    }
}

#endif
