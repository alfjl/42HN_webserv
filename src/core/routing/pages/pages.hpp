#ifndef WEBSERV_CORE_ROUTING_PAGES_PAGES_HPP
#define WEBSERV_CORE_ROUTING_PAGES_PAGES_HPP

#include "../../../http/response.hpp"

namespace webserv {
    namespace core {

		std::string itos(unsigned int code);

		void error_code(webserv::http::response_fixed& response, unsigned int code);
		void permanent_redirect_301(webserv::http::response_fixed& response, webserv::util::path path);
		void temporary_redirect_302(webserv::http::response_fixed& response, webserv::util::path path);
		void bad_request_400(webserv::http::response_fixed& response);
		void unauthorized_401(webserv::http::response_fixed& response);
		void not_found_404(webserv::http::response_fixed& response);
		void method_not_allowed_405(webserv::http::response_fixed& response);
		void gone_410(webserv::http::response_fixed& response);
		void teapot_418(webserv::http::response_fixed& response);
		void internal_server_error_500(webserv::http::response_fixed& response);
		void service_unavailable_503(webserv::http::response_fixed& response);

    }
}

#endif
