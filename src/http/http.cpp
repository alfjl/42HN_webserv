#include "http.hpp"

namespace webserv {
    namespace http {

		std::string find_mime(std::string extension) {
            if (extension == "bmp")
                return "image/bmp";
            else if (extension == "css")
                return "text/css";
            else if (extension == "csv")
                return "text/csv";
            else if (extension == "doc")
                return "application/msword";
            else if (extension == "docx")
                return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
            else if (extension == "gif")
                return "image/gif";
            else if ((extension == "html") || (extension == "htm"))
                return "text/html";
            else if ((extension == "jpeg") || (extension == "jpg"))
                return "image/jpeg";
            else if (extension == "js")
                return "text/javascript";
            else if (extension == "json")
                return "application/json";
            else if (extension == "png")
                return "image/png";
            else if (extension == "pdf")
                return "application/pdf";
            else if (extension == "php")
                return "application/x-httpd-php";
            else if (extension == "txt")
                return "text/plain";
            else
                return "*/*";
        }

        /*
         * Accepts a http status_code and returns the matching status message
         */
        const char* code2str(unsigned int code) {
            switch (code) {
                // 1xx informational response
                case 100: return "Continue";
                case 101: return "Switching Protocol";
                case 102: return "Processing";
                case 103: return "Early Hints";

                // 2xx success
                case 200: return "OK";
                case 201: return "Created";
                case 202: return "Accepted";
                case 203: return "Non-Authoritative Information";
                case 204: return "No Content";
                case 205: return "Reset Content";
                case 206: return "Partial Content";
                case 207: return "Multi-Status";
                case 208: return "Already Reported";
                case 226: return "IM Used";

                // 3xx redirection
                case 300: return "Multiple Choices";
                case 301: return "Moved permanently";
                case 302: return "Found";
                case 303: return "See Other";
                case 304: return "Not Modified";
                case 305: return "Use Proxy";
                case 306: return "unused";
                case 307: return "Temporary Redirect";
                case 308: return "Permanent Redirect";

                // 4xx client errors
                case 400: return "Bad Request";
                case 401: return "Unauthorized";
                case 402: return "Payment Required";
                case 403: return "Forbidden";
                case 404: return "Not Found";
                case 405: return "Method Not Allowed";
                case 406: return "Not Acceptable";
                case 407: return "Proxy Authentication Required";
                case 408: return "Request Timeout";
                case 409: return "Conflict";
                case 410: return "Gone";
                case 411: return "Length Required";
                case 412: return "Precondition Failed";
                case 413: return "Payload Too Large";
                case 414: return "URI Too Long";
                case 415: return "Unsupported Media Type";
                case 416: return "Range Not Satisfiable";
                case 417: return "Expectation Failed";
                case 418: return "I'm a teapot";
                case 421: return "Misdirected Request";
                case 422: return "Unprocessable Entity";
                case 423: return "Locked";
                case 424: return "Failed Dependency";
                case 425: return "Too Early";
                case 426: return "Upgrade Required";
                case 428: return "Precondition Required";
                case 429: return "Too Many Requests";
                case 431: return "Request Header Fields Too Large";
                case 451: return "Unavailable For Legal Reasons";

                // Unofficial codes: nginx
                case 444: return "No Response";
                case 494: return "Request header too large";
                case 495: return "SSL Certificate Error";
                case 496: return "SSL Certificate Required";
                case 497: return "HTTP Request Sent to HTTPS Port";
                case 499: return "Client Closed Request";

                // 5xx server errors
                case 500: return "Internal Server Error";
                case 501: return "Not Implemented";
                case 502: return "Bad Gateway";
                case 503: return "Service Unavailable";
                case 504: return "Gateway Timeout";
                case 505: return "HTTP Version Not Supported";
                case 506: return "Variant Also Negotiates";
                case 507: return "Insufficient Storage";
                case 508: return "Loop Detected";
                case 510: return "Not Extended";
                case 511: return "Network Authentication Required";
                default: return "I'm a teapot";
            }
        }


    }
}