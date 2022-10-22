#include "response.hpp"

namespace webserv {
    namespace http {

        /*
         * Default constructor default-initializes the members
         */
        response::response() : _fields(), _code(418), _block_mode(block_mode_none) {

        }

        /*
         * Extracts the ostream of the connection
         * and passes it on as its return value
         */
        std::ostream& response::out(webserv::util::connection& con) {
            return con.get_ostream();
        }

        unsigned int response::get_code() const {
            return _code;
        }

        /*
         * Sets status code in instance
         */
        void response::set_code(unsigned int code) {
            _code = code;
        }

        /*
         * Sets a new field with pair name and value
         */
        void response::set_field(std::string name, std::string value) {
            _fields.put(name, value);
        }

        /*
         * Writes the status_code and corresponding message (e.g. 200 OK)
         * of the response to the connection
         */
        void    response::write_status(webserv::util::connection& con) {
            out(con) << _code << " " << webserv::http::code2str(_code) << "\r\n";
        }

        /*
         * Iterates over the _fields member
         * and writes field by field to the connection
         */
        void    response::write_fields(webserv::util::connection& con) {
            fields::const_iterator  it = _fields.begin();
            fields::const_iterator  ite = _fields.end();

            for (; it != ite; ++it) {
                out(con) << it->first;
                out(con) << ": ";
                out(con) << it->second;
                out(con) << "\r\n";
            }

            // TODO: Remove these later
            out(con) << "Server: Webserv/0.1\r\n";
        }

        /*
         * Accepts a status code and writes the correct response back
         * to the connections ostream
         */
        void    response::write(webserv::util::connection& con) {
            if (_block_mode == block_mode_all) return;

            out(con) << "HTTP/1.1 ";
            // write code + corresponding message (e.g. 200 OK)
            write_status(con);
            // iterate over fields, and write all fields
            write_fields(con);
            // write CRLF before begin of body
            out(con) << "\r\n";
            // write response body
            if (_block_mode == block_mode_none)
                write_body(con);
        }

        void response::block_body() {
            _block_mode = block_mode_body;
        }

        void response::block_all() {
            _block_mode = block_mode_all;
        }


        /*
         * Default constructor default-initializes the members in base class
         */
        response_fixed::response_fixed() : response() {

        }

        /*
         * Extracts the ostream of the connection
         * and passes it on as its return value
         */
        std::ostream& response_fixed::out(webserv::util::connection& con) {
            return response::out(con);
        }

        /*
         * Sets status code in base class
         */
        void response_fixed::set_code(unsigned int code) {
            response::set_code(code);
        }

        /*
         * Sets a new field in base class with pair name and value
         */
        void response_fixed::set_field(std::string name, std::string value) {
            response::set_field(name, value);
        }

        /*
         * Sets _body and field 'Content-type' for html responses 
         */
        void response_fixed::set_html_body(std::string body) {
            set_body(body, "text/html");
        }

        /*
         * Sets string body as the base class' _body & field Content-type in accordance with MIME-type 'content_type'
         */
        void response_fixed::set_body(std::string body, std::string content_type) {
            if (_block_mode != block_mode_all) {
                _body = body;
                set_field("Content-type", content_type);
            }
        }

        /*
         * Writes the body of the response to the connections ostream
         */
        void    response_fixed::write_body(webserv::util::connection& con) {
                out(con) << _body;
        }

        /*
         * Accepts a status code and writes the correct response back
         * to the connections ostream
         */
        void    response_fixed::write(webserv::util::connection& con) {
            response::write(con);
        }

    }
}
