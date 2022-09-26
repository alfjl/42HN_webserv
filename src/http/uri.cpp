#include "uri.hpp"

namespace webserv {
    namespace http {

        /*
         * returns a concatenated string of all elements of _addr
         */
        std::string path::get_addr() const {
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

        void path::mov_cd(std::string& new_addr) {
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

        std::ostream& operator<<(std::ostream& stream, const path& the_path) {
            stream << the_path.get_addr();
            return stream;
        }




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
