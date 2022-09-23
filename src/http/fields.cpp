#include "fields.hpp"

namespace webserv {
    namespace http {

        fields::fields() {}
        fields::~fields() {}

        std::string fields::get_or_default(std::string key, std::string deflt) const {
            std::map<std::string, std::string>::const_iterator it = _fields.find(key);
            if (it == _fields.end()) return deflt;
            else                     return it->second;
        }

        void fields::put(std::string key, std::string value) {
            _fields[key] = value;
        }

        typename fields::const_iterator fields::begin() const
        {
            return ( this->_fields.begin() );
        }

        typename fields::const_iterator fields::end() const
        {
            return ( this->_fields.end() );
        }

    }
}
