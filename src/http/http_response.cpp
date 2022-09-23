#include "http_response.hpp"

namespace webserv {
    namespace http {

        /*
         * Default constructor initializes the members
         * with members from http_request
         */
        http_response::http_response(webserv::http::request_core& request)
            : _fields(request.get_fields()), _code(0) {

        }

        /*
         * Extracts the ostream of the connection
         * and passes it on as its return value
         */
        std::ostream& http_response::out(webserv::util::connection& con) {
            return con.get_ostream();
        }

        /*
         * Writes the status_code and corresponding message (e.g. 200 OK)
         * of the http_response to the connection
         */
        void    http_response::write_status(webserv::util::connection& con) {
            switch (_code)
            {
                // 1xx informational response
                case 100:
                    out(con) << "100 Continue\r\n";
                case 101:
                    out(con) << "101 Switching Protocol\r\n";
                case 102:
                    out(con) << "102 Processing\r\n";
                case 103:
                    out(con) << "103 Early Hints\r\n";

                // 2xx success
                case 200:
                    out(con) << "200 OK\r\n";
                case 201:
                    out(con) << "201 Created\r\n";
                case 202:
                    out(con) << "202 Accepted\r\n";
                case 203:
                    out(con) << "203 Non-Authoritative Information\r\n";
                case 204:
                    out(con) << "204 No Content\r\n";
                case 205:
                    out(con) << "205 Reset Content\r\n";
                case 206:
                    out(con) << "206 Partial Content\r\n";
                case 207:
                    out(con) << "207 Multi-Status\r\n";
                case 208:
                    out(con) << "208 Already Reported\r\n";
                case 226:
                    out(con) << "226 IM Used\r\n";

                // 3xx redirection
                case 300:
                    out(con) << "300 Multiple Choices\r\n";
                case 301:
                    out(con) << "301 Moved permanently\r\n";
                case 302:
                    out(con) << "302 Found\r\n";
                case 303:
                    out(con) << "303 See Other\r\n";
                case 304:
                    out(con) << "304 Not Modified\r\n";
                case 305:
                    out(con) << "305 Use Proxy\r\n";
                case 306:
                    out(con) << "306 unused\r\n";
                case 307:
                    out(con) << "307 Temporary Redirect\r\n";
                case 308:
                    out(con) << "308 Permanent Redirect\r\n";

                // 4xx client errors
                case 400:
                    out(con) << "400 Bad Request\r\n";
                case 401:
                    out(con) << "401 Unauthorized\r\n";
                case 402:
                    out(con) << "402 Payment Required\r\n";
                case 403:
                    out(con) << "403 Forbidden\r\n";
                case 404:
                    out(con) << "404 Not Found\r\n";
                case 405:
                    out(con) << "405 Method Not Allowed\r\n";
                case 406:
                    out(con) << "406 Not Acceptable\r\n";
                case 407:
                    out(con) << "407 Proxy Authentication Required\r\n";
                case 408:
                    out(con) << "408 Request Timeout\r\n";
                case 409:
                    out(con) << "409 Conflict\r\n";
                case 410:
                    out(con) << "410 Gone\r\n";
                case 411:
                    out(con) << "411 Length Required\r\n";
                case 412:
                    out(con) << "412 Precondition Failed\r\n";
                case 413:
                    out(con) << "413 Payload Too Large\r\n";
                case 414:
                    out(con) << "414 URI Too Long\r\n";
                case 415:
                    out(con) << "415 Unsupported Media Type\r\n";
                case 416:
                    out(con) << "416 Range Not Satisfiable\r\n";
                case 417:
                    out(con) << "417 Expectation Failed\r\n";
                case 418:
                    out(con) << "418 I’m a teapot\r\n";
                case 421:
                    out(con) << "421 Misdirected Request\r\n";
                case 422:
                    out(con) << "422 Unprocessable Entity\r\n";
                case 423:
                    out(con) << "423 Locked\r\n";
                case 424:
                    out(con) << "424 Failed Dependency\r\n";
                case 425:
                    out(con) << "425 Too Early\r\n";
                case 426:
                    out(con) << "426 Upgrade Required\r\n";
                case 428:
                    out(con) << "428 Precondition Required\r\n";
                case 429:
                    out(con) << "429 Too Many Requests\r\n";
                case 431:
                    out(con) << "431 Request Header Fields Too Large\r\n";
                case 451:
                    out(con) << "451 Unavailable For Legal Resons\r\n";

                // Unofficial codes: nginx // TODO: nginx codes needed?
                case 444:
                    out(con) << "444 No Response\r\n";
                case 494:
                    out(con) << "494 Request header too large\r\n";
                case 495:
                    out(con) << "495 SSL Certificate Error\r\n";
                case 496:
                    out(con) << "496 SSL Certificate Required\r\n";
                case 497:
                    out(con) << "497 HTTP Request Sent to HTTPS Port\r\n";
                case 499:
                    out(con) << "499 Client Closed Request\r\n";

                // 5xx server errors
                case 500:
                    out(con) << "500 Internal Server Error\r\n";
                case 501:
                    out(con) << "501 Not Implemented\r\n";
                case 502:
                    out(con) << "502 Bad Gateway\r\n";
                case 503:
                    out(con) << "503 Service Unavailable\r\n";
                case 504:
                    out(con) << "504 Gateway Timeout\r\n";
                case 505:
                    out(con) << "505 HTTP Version Not Supported\r\n";
                case 506:
                    out(con) << "506 Variant Also Negotiates\r\n";
                case 507:
                    out(con) << "507 Insufficient Storage\r\n";
                case 508:
                    out(con) << "508 Loop Detected\r\n";
                case 510:
                    out(con) << "510 Not Extended\r\n";
                case 511:
                    out(con) << "511 Network Authentication Required\r\n";
                default: // TODO: needed? 
                    out(con) << "500 Internal Server Error\r\n";
            }
        }

        /*
         * Iterates over the _fields member
         * and writes field by field to the connection
         */
        void    http_response::write_fields(webserv::util::connection& con) {
            fields::const_iterator  it = _fields.begin();
            fields::const_iterator  ite = _fields.end();

            for (; it != ite; ++it) {
                out(con) << it->first;
                out(con) << ":"; // TODO: Do we need to take care of the spaces before and after the ':'? The parsers seems to skip them!
                out(con) << it->second;
                out(con) << "\r\n"; // TODO: Needed? The parser seems to not save them in 'into.value'.
            }
        }

        /*
         * Writes the body of the http_response to the connections ostream
         */
        void    http_response::write_body(webserv::util::connection& con) { // TODO: just for testing so far! Needs to be adaptet later!

                std::string response;

                response += "<html><head></head><body>";
                response += "<br/>   ---  WHATS OUR BODY???  ---   <br/>";
                response += "</body></html>";
                out(con) << response;
        }

        /*
         * Accepts a status code and writes the correct response back
         * to the connections ostream
         */
        void    http_response::write(int code, webserv::util::connection& con) {
            _code = code;

            out(con) << "\n\n ------------- TEST BEGIN --------------\n"; // TODO: Delete! Testing purposes only!
            out(con) << "HTTP/1.1 "; // TODO: do we need to write "HTTP/1.1" in every case? If yes, with or without trailing space?
            // write code + corresponding message (e.g. 200 OK)
            write_status(con);
            // iterate over fields, and write all fields
            write_fields(con);
            // write CRLF before begin of body
            out(con) << "\r\n";
            // write response body
            write_body(con);
            out(con) << "\n\n ------------- TEST END --------------\n"; // TODO: Delete! Testing purposes only!
        }

    } // namespace http
} // namespace webserv
