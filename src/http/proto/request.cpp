#include "request.hpp"

namespace webserv {
    namespace http {

		void request_line::set_method(enum http_method m) { _method = m; }
		uri& request_line::get_uri() { return _uri; }
		http_version& request_line::get_version() { return _http_version; }
		http_method&  request_line::get_method() { return _method; }


		request::request() { _fields.case_insensitive(); }

        request_line&                      request::get_line()   { return _line;   }
        fields&                            request::get_fields() { return _fields; }
        webserv::util::binary_buffer&      request::get_body()   { return _body;   }
        webserv::pal::net::ip_connection&  request::get_conn()   { return _conn;   }
		
    }
}