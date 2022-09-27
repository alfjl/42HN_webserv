#include "uri.hpp"

namespace webserv {
    namespace http {

        /* ---------------------- PATH -------------------------------------- */

        /*
         * returns a copy of _addr
         */
        std::vector<std::string> path::get_addr() {
            return _addr;
        }

        /*
         * returns a concatenated string of all elements of _addr
         */
        std::string path::get_addr_s() const {
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

        std::string path::get_first() {
            if (_addr.empty()) return "";
            return _addr[0];
        }

        std::string path::get_last() {
            if (_addr.empty()) return "";
            return _addr[_addr.size() - 1];
        }
        
        path path::get_rest() {
            std::vector<std::string> v(_addr);
            if (!v.empty())
                v.erase(v.begin());
            return path(v);
        }

        /*
         * Checks if prefix is beginning of this->_addr
         */
        // can we use algorithm.search(ForwardIt1 first, ForwardIt1 last,
        //                             ForwardIt2 s_first, ForwardIt2 s_last) instead?
        bool path::begins_with(path prefix) {
            size_t size_p = prefix._addr.size();
            size_t size_this = this->_addr.size();

            for (size_t i = 0; i < size_p; ++i) {
                if (i >= size_this
                || prefix._addr[i] != this->_addr[i]) // do we need to pull these apart in 2 ifs?
                    return false;
            }
            return true;
        }

        path path::adapt_prefix(path old_prefix, path new_prefix) {
            path v(_addr);
            
            for (size_t i = 0; i < old_prefix.size(); ++i) {
                v = this->get_rest();
            }
            return new_prefix + v;
        }

        /*
         * Iterates over all strings in _addr of this and rhs
         * and checks, if value is equal
         */
        bool path::is_equal(const path& rhs) const {
            size_t size_lhs = this->size();
            size_t size_rhs = rhs.size();

            for (size_t i = 0; i < size_lhs; ++i) {
                if (i >= size_rhs
                || this->_addr[i] != rhs._addr[i]) // do we need to pull these apart in 2 ifs?
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
            stream << the_path.get_addr_s();
            return stream;
        }

        /* ---------------------- URI --------------------------------------- */

        uri::uri() : _proto("http"), _server(""), _port(80), _path() {

        }

        uri::~uri() {

        }

        std::ostream& operator<<(std::ostream& stream, const uri& the_uri) {
            stream << the_uri.get_proto() << " | " << the_uri.get_server() << " | " << the_uri.get_port() << " | /" << the_uri.get_path();
            return stream;
        }
    }
}
