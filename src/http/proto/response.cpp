#include "response.hpp"

namespace webserv {
    namespace http {

        /*
         * Default constructor default-initializes the members
         */
        response::response() : _fields(), _code(418), _code_locked(false), _block_mode(block_mode_none), _is_cgi(false) {

        }

        void response::enable_cgi_mode() {
            _is_cgi = true;
        }

        unsigned int response::get_code() const {
            return _code;
        }

        /*
         * Sets status code in instance
         */
        void response::set_code(unsigned int code) {
            if (!_code_locked) {
                _code = code;
            }
        }

        void response::lock_code(unsigned int code) {
            set_code(code);
            _code_locked = true;
        }

        /*
         * Sets a new field with pair name and value
         */
        void response::set_field(std::string name, std::string value) {
            _fields.put(name, value);
        }

        void response::set_field(std::string name, int value) {
            _fields.put(name, value);
        }

        /*
         * Writes the status_code and corresponding message (e.g. 200 OK)
         * of the response to the connection
         */
        void    response::write_status(std::ostream& stream) {
            if (_is_cgi)
                stream << "Status: ";
            else
                stream << "HTTP/1.1 ";
            stream << _code << " " << webserv::http::code2str(_code) << "\r\n";
        }

        /*
         * Iterates over the _fields member
         * and writes field by field to the connection
         */
        void    response::write_fields(std::ostream& stream) {
            fields::const_iterator  it = _fields.begin();
            fields::const_iterator  ite = _fields.end();

            for (; it != ite; ++it) {
                stream << it->first;
                stream << ": ";
                stream << it->second;
                stream << "\r\n";
            }

            // TODO: Remove these later = Should this be the name, that we get from config "server_name"?
            stream << "Server: Webserv/0.1\r\n";
        }

        /*
         * Accepts a status code and writes the correct response back
         * to the connections ostream
         */
        void    response::write(std::ostream& stream) {
            if (_block_mode == block_mode_all) return;

            // write code + corresponding message (e.g. 200 OK)
            write_status(stream);
            // iterate over fields, and write all fields
            write_fields(stream);
            // write CRLF before begin of body
            stream << "\r\n";
            // write response body
            if (_block_mode == block_mode_none)
                write_body(stream);
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
         * Sets a new field in base class with pair name and value
         */
        void response_fixed::set_field(std::string name, std::string value) {
            response::set_field(name, value);
        }

        void response_fixed::set_field(std::string name, int value) {
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
                _body.assign(body);
                set_field("Content-type", content_type);
                set_field("Content-Length", _body.size());
            }
        }

        void response_fixed::set_body(webserv::util::binary_buffer& buf, std::string content_type) {
            if (_block_mode != block_mode_all) {
                _body.assign(buf);
                set_field("Content-type", content_type);
                set_field("Content-Length", _body.size());
            }
        }

        /*
         * Writes the body of the response to the connections ostream
         */
        void response_fixed::write_body(std::ostream& stream) {
            _body.write_to_stream(stream);
        }

        /*
         * Accepts a status code and writes the correct response back
         * to the connections ostream
         */
        void response_fixed::write(std::ostream& stream) {
            response::write(stream);
        }

        void response_fixed::write(webserv::util::connection& con) {
            write(con.get_ostream());
        }

    }
}
