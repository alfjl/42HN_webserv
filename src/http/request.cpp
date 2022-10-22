#include "request.hpp"

namespace webserv {
    namespace http {

		void request_line::set_method(enum http_method m) { _method = m; }
		uri& request_line::get_uri() { return _uri; }
		http_version& request_line::get_version() { return _http_version; }
		http_method&  request_line::get_method() { return _method; }


		request_core::request_core() { _fields.case_insensitive(); }

        request_line& request_core::get_line()   { return _line;   }
        fields&       request_core::get_fields() { return _fields; }
        std::string&   request_core::get_body() { return _body; }
		
    }
}