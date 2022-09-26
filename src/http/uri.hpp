#ifndef WEBSERV_HTTP_URI_HPP
#define WEBSERV_HTTP_URI_HPP

#include "../defs.hpp"

namespace webserv {
    namespace http {

        class path {
        public:
            typedef std::vector<std::string>::const_iterator const_iterator;

        private:
            std::vector<std::string>   _addr;

        private:
            path(std::vector<std::string> addr);

        public:
            path();
            path(std::string addr);
            ~path();


            const_iterator begin() const;
            const_iterator end() const;

            // operator+(element von _addr, element von _addr)
            // operator+=(element von _addr, element von _addr)
            // expose vector iterator as const_iterator
            // void up() // loescht get_last() und erzeugt neue Instanz von path = destruktiv
            //( oder path up() // nicht destruktiv, sondern Kopie einer neuen path Instanz samt Aenderungen)
            // path cd(std::string& dir) // haengt string an _addr an, ausser es ist "." oder "", dies tut nix. ".." called up() 
            // selbe wie bei up()
        private:
            void mov_up();
            void mov_cd1(std::string dir);
            void mov_cd(std::string& new_addr);
        
        public:
            // void cd1()
            // path mov_cd1();
 
            // get_first() // erstes Element von _addr
            // get_last() // letztes Element von _addr
            // get_rest() // alle elemente von _addr ausser first

            std::string get_addr() const; // returnes concatenated string von allen elementen von _addr
        };

        std::ostream& operator<<(std::ostream& stream, const path& the_path);

        class uri {
            std::string   _proto;
            std::string   _server;
            unsigned int  _port;
            path          _path;
        public:
            uri();
            ~uri();

            std::string& get_proto() { return _proto; }
            std::string& get_server() { return _server; }
            unsigned int& get_port() { return _port; }
            path& get_path() { return _path; }

            const std::string& get_proto() const { return _proto; }
            const std::string& get_server() const { return _server; }
            unsigned int get_port() const { return _port; }
            const path& get_path() const { return _path; }
        };

        std::ostream& operator<<(std::ostream& stream, const uri& the_uri);

    }
}

#endif
