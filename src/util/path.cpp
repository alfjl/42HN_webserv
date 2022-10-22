#include "path.hpp"

namespace webserv {
    namespace util {

        /*
         * returns a concatenated string of all elements of _addr
         */
        std::string path::to_relative_string() const {
            std::string concatenated_addr;

            const_iterator it = _addr.begin();
            const_iterator ite = _addr.end();
            for (; it != ite; ++it) {
                if (it != _addr.begin())
                    concatenated_addr += "/";
                concatenated_addr += *it;
            }
            return (concatenated_addr);
        }

        std::string path::to_absolute_string() const {
            return "/" + to_relative_string();
        }


        path::path() {

        }

        path::path(std::string addr) : _addr() {
            mov_cd(addr);
        }

        path::path(std::vector<std::string> addr) : _addr(addr) {

        }

        path::~path() {

        }

        path::const_iterator path::begin() const
        {
            return ( this->_addr.begin() );
        }

        path::const_iterator path::end() const
        {
            return ( this->_addr.end() );
        }

        size_t path::size() const {
            return _addr.size();
        }


        void path::mov_up() {
            if (!_addr.empty())
                _addr.pop_back();
        }

        void path::mov_cd1(std::string dir) {
            if (dir == "" || dir == ".")
                ;
            else if (dir == "..")
                mov_up();
            else
                _addr.push_back(dir);
        }

        void path::mov_cd(std::string new_addr) {
            size_t i = 0;

            if (new_addr.find("/") == 0) {
                _addr.clear();
            }

            do {
                size_t i2 = new_addr.find("/", i);
                std::string elem = new_addr.substr(i, i2 - i);
                mov_cd1(elem);
                i = i2 + ((i2 != std::string::npos) ? 1 : 0);
            } while (i != std::string::npos);
        }

        path path::cd(std::string dirs) {
            path p(*this);
            p.mov_cd(dirs);
            return p;
        }

        std::string path::get_first() const {
            if (_addr.empty()) return "";
            return _addr[0];
        }

        std::string path::get_last() const {
            if (_addr.empty()) return "";
            return _addr[_addr.size() - 1];
        }
        
        path path::get_rest() const {
            std::vector<std::string> v(_addr);
            if (!v.empty())
                v.erase(v.begin());
            return path(v);
        }

        /*
         * Checks if prefix is beginning of this->_addr
         */
        bool path::begins_with(path prefix) {
            size_t size_p = prefix._addr.size();

            if (prefix.size() > size()) return false;

            for (size_t i = 0; i < size_p; ++i) {
                if (prefix._addr[i] != this->_addr[i])
                    return false;
            }

            return true;
        }

        /*
         * Substitute old_prefix with new_prefix in this->_addr
         */
        path path::adapt_prefix(path old_prefix, path new_prefix) {
            path v(_addr);
            
            for (size_t i = 0; i < old_prefix.size(); ++i) {
                v = this->get_rest();
            }
            return new_prefix + v;
        }

        /*
         * Extracts and returns everything after the last '.'
         * Calling function needs to check validity
         */
        std::string path::get_extension() {
            std::string extension = get_last();

            size_t i = extension.rfind('.', extension.length());
            if (i != std::string::npos) {
                return(extension.substr(i + 1, extension.length() - i));
            }
            return "";
        }

        /*
         * Iterates over all strings in _addr of this and rhs
         * and checks, if string is equal
         * Returns true, if all strings are equal
         */
        bool path::is_equal(const path& rhs) const {
            size_t size_lhs = this->size();
            size_t size_rhs = rhs.size();

            if (size_lhs != size_rhs) return false;
            
            for (size_t i = 0; i < size_lhs; ++i) {
                if (this->_addr[i] != rhs._addr[i])
                    return false;
            }

            return true;
        }

        path operator+(const path& a, const path& b) {
            path new_path;

            path::const_iterator  it = a.begin();
            path::const_iterator  ite = a.end();
            for (; it != ite; ++it)
                new_path.mov_cd(*it);

            it = b.begin();
            ite = b.end();
            for (; it != ite; ++it)
                new_path.mov_cd(*it);
            
            return new_path;
        }

        bool operator==(const path& lhs, const path& rhs) {
            return (lhs.is_equal(rhs));
        }


        std::ostream& operator<<(std::ostream& stream, const path& the_path) {
            stream << the_path.to_relative_string();
            return stream;
        }

    }
}
