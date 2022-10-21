#include "pages.hpp"

#include "../cgi/cgi.hpp"
#include "../../../pal/cpp/conv.hpp"

namespace webserv {
    namespace http {

        const char* code2str(unsigned int code); // TODO: Move to utility directory

    }

    namespace core {

        // std::string itos(unsigned int code){
        //     std::ostringstream ost;
        //     ost << code;
        //     return ost.str();
        // }

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

        void error_code(webserv::http::response_fixed& response, unsigned int code) {
            std::ostringstream ost;
                
            std::pair<std::string, std::string> quote("Ah, there's nothing like the hot winds of Hell blowing in your face.", "- Le Chuck"); // Todo: code2str for monkey island quotes!

            std::string buf(webserv::pal::cpp::int_to_string(code));
            buf.append(" ");
            buf.append(webserv::http::code2str(code));
            ost << "<!DOCTYPE html>\r\n";
            ost << "<html>\r\n";
            head_start(ost, buf);
            ost << "<body>\r\n";
            header_one(ost, "Error at WebServ!");
            blockquote(ost, quote);
            header_three(ost, buf);
            ost << "</body>\r\n";
            ost << "</html>\r\n";

            response.set_code(code);
            response.set_html_body(ost.str());
        }

        void permanent_redirect_301(webserv::http::response_fixed& response, webserv::util::path path) {
            error_code(response, 301); 
            response.set_field("Location", path.to_absolute_string());
        }

        void temporary_redirect_302(webserv::http::response_fixed& response, webserv::util::path path) {
            error_code(response, 302);
            response.set_field("Location", path.to_absolute_string());
        }

        void bad_request_400(webserv::http::response_fixed& response) {
            error_code(response, 400);
        }

        void unauthorized_401(webserv::http::response_fixed& response) {
            error_code(response, 401);
        }

        void not_found_404(webserv::http::response_fixed& response) {
            error_code(response, 404);
        }

        void method_not_allowed_405(webserv::http::response_fixed& response) {
            error_code(response, 405);
        }

        void gone_410(webserv::http::response_fixed& response) {
            error_code(response, 410);
        }

        void teapot_418(webserv::http::response_fixed& response) {
            error_code(response, 418);
        }

        void internal_server_error_500(webserv::http::response_fixed& response) {
            error_code(response, 500);
        }

        void service_unavailable_503(webserv::http::response_fixed& response) {
            error_code(response, 503);
        }

	}
}
