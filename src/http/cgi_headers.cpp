#include "cgi_headers.hpp"

namespace webserv {
    namespace http {

        cgi_headers::cgi_headers() {}
        cgi_headers::~cgi_headers() {}

        bool cgi_headers::has(std::string key) const {
            return _headers.find(key) != _headers.end();
        }

        std::string cgi_headers::get_or_default(std::string key, std::string deflt) const {
            std::map<std::string, std::string>::const_iterator it = _headers.find(key);
            if (it == _headers.end()) return deflt;
            else                     return it->second;
        }

        void cgi_headers::put(std::string key, std::string value) {
            _headers[key] = value;
        }

        cgi_headers::const_iterator cgi_headers::begin() const
        {
            return ( this->_headers.begin() );
        }

        cgi_headers::const_iterator cgi_headers::end() const
        {
            return ( this->_headers.end() );
        }


        std::ostream& operator<<(std::ostream& stream, const cgi_headers& the_headers) {
            std::map<std::string, std::string>::const_iterator it = the_headers.begin();
            std::map<std::string, std::string>::const_iterator ite = the_headers.end();

            for (; it != ite; ++it) {
                stream << it->first;
                stream << ":";
                stream << it->second;
                stream << "\r\n";
            }
            
            return stream;
        }

    }
}
