#include "fields.hpp"

namespace webserv {
    namespace http {

        fields::fields() {}
        fields::~fields() {}

        bool fields::has(std::string key) const {
            return _fields.find(key) != _fields.end();
        }

        std::string fields::get_or_default(std::string key, std::string deflt) const {
            std::map<std::string, std::string>::const_iterator it = _fields.find(key);
            if (it == _fields.end()) return deflt;
            else                     return it->second;
        }

        void fields::put(std::string key, std::string value) {
            _fields[key] = value;
        }

        void fields::put(std::string key, int value) {
            std::ostringstream  o;

            o << value;
            put(key, o.str());
        }

        fields::const_iterator fields::begin() const
        {
            return ( this->_fields.begin() );
        }

        fields::const_iterator fields::end() const
        {
            return ( this->_fields.end() );
        }


        std::ostream& operator<<(std::ostream& o, fields f) {
            fields::const_iterator it  = f.begin();
            fields::const_iterator ite = f.end();

            for (; it != ite; ++it) {
                o << it->first << ": " << it->second << "\r\n";
            }

            return o;
        }

    }
}
