#include "../pal/cpp/conv.hpp"

#include "fields.hpp"

namespace webserv {
    namespace http {

        fields::fields() : _case_sensitive(true) {}
        fields::~fields() {}

        bool fields::get(std::string key, std::string& value) const {
            std::string key_lower;
            std::string::const_iterator it = key.begin();
            std::string::const_iterator ite = key.end();

            for (; it != ite; ++it)
                key_lower += (_case_sensitive) ? (*it) : (::tolower(*it));

            std::map<std::string, std::string>::const_iterator it2 = _fields.find(key_lower);
            if (it2 == _fields.end()) { return false; }
            else { value = it2->second; return true; }
        }

        bool fields::has(std::string key) const {
            return _fields.find(key) != _fields.end();
        }

        std::string fields::get_or_default(std::string key, std::string deflt) const {
            std::string res;

            return get(key, res) ? res : deflt;
        }

        bool fields::get_int_or_default(std::string key, int& value, int default_value) const {
            std::string v;

            if (get(key, v)) {
                return webserv::pal::cpp::string_to_int(v.c_str(), value);
            } else {
                value = default_value;
                return true;
            }
        }

        int fields::get_int_or_default(std::string key, int default_value) const {
            int v;

            get_int_or_default(key, v, default_value);
            return v;
        }

        void fields::put(std::string key, std::string value) {
            std::string key_lower;

            std::string::const_iterator it = key.begin();
            std::string::const_iterator ite = key.end();
            for (; it != ite; ++it)
                key_lower += (_case_sensitive) ? (*it) : (::tolower(*it));
            _fields[key_lower] = value;
        }

        void fields::put(std::string key, int value) {
            std::ostringstream  o;

            o << value;
            put(key, o.str());
        }

        void fields::remove(std::string key) {
            std::string key_lower;
            std::string::const_iterator it = key.begin();
            std::string::const_iterator ite = key.end();

            for (; it != ite; ++it)
                key_lower += (_case_sensitive) ? (*it) : (::tolower(*it));

            std::map<std::string, std::string>::iterator it2 = _fields.find(key_lower);
            if (it2 != _fields.end()) { _fields.erase(it2); }
        }

        void fields::case_insensitive() {
            _case_sensitive = false;
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
