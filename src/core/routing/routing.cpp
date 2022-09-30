#include "routing.hpp"

#include "routing_table.hpp"
#include "../instance.hpp"
#include "../../http/response.hpp"


namespace webserv {

    namespace http {
        const char* code2str(unsigned int code); // TODO: Move to utility directory
    }

    namespace core {

        routing::routing(instance& the_inst) : component(the_inst) {

        }

        routing::~routing() {

        }

        webserv::http::response_fixed* routing::look_up(webserv::http::request_core& request) {
            webserv::http::response_fixed *response = new webserv::http::response_fixed();

            switch (request.get_line().get_method()) {
                // case webserv::http::http_method_options: std::cout << "TODO: case http_method_options:" << std::endl; break;
                case webserv::http::http_method_get: {
                    webserv::core::routing_table table;
                    webserv::util::path file_path = table.query(request.get_line().get_uri().get_path());
                    std::ifstream stream;
                    if (get_instance().get_fs().is_directory(file_path)) {
                        directory_listing(response, get_instance().get_fs().read_absolute_path(file_path));
                    } else if (get_instance().get_fs().open(file_path, stream)) {
                        std::ostringstream payload;
                        while (!stream.eof()) {
                            char c;
                            stream.get(c);
                            payload << c;
                        }
                        std::cout << "Done!" << std::endl;

                        response->set_code(200);
                        response->set_body(payload.str(), find_mime(file_path.get_extension()));
                    } else {
                        not_found_404(response);
                    }

                    break;
                }
                // case webserv::http::http_method_head: std::cout << "TODO: case http_method_head:" << std::endl; break;
                case webserv::http::http_method_post: std::cout << "TODO: case http_method_post:" << std::endl;
                // case webserv::http::http_method_put: std::cout << "TODO: case http_method_put:" << std::endl; break;
                case webserv::http::http_method_delete: std::cout << "TODO: case http_method_delete:" << std::endl;
                // case webserv::http::http_method_trace: std::cout << "TODO:case http_method_trace:" << std::endl; break;
                // case webserv::http::http_method_connect: std::cout << "TODO: case http_method_connect:" << std::endl; break;
                default: {
                    teapot_418(response);
                    break;
                }
            }
            return (response);
        }

        void routing::tick() {
            // Do nothing!
        }

        void routing::directory_listing(webserv::http::response_fixed* response, std::vector<webserv::util::path> paths) {
            std::ostringstream ost;
            
            ost << "<!DOCTYPE html>\r\n";
            ost << "<html>\r\n";
            ost << "<head>\r\n";
            ost << "<meta charset=\"UTF-8\" />\r\n";
            ost << "<title>Listing</title>\r\n";
            ost << "</head>\r\n";
            ost << "<body>\r\n";

            std::vector<webserv::util::path>::const_iterator it = paths.begin();
            while (it != paths.end()) {
                ost << "<a href=\"/" << (*it) << "\">" << (*it).get_last() << "</a>";
                ost << "<br/>\r\n";
                ++it;
            }

            ost << "</body>\r\n";
            ost << "</html>\r\n";

            response->set_code(200);
            response->set_html_body(ost.str());
        }

        void routing::error_code(webserv::http::response_fixed* response, unsigned int code) {
            std::ostringstream ost;
                
            std::pair<std::string, std::string> quote("Ah, there's nothing like the hot winds of Hell blowing in your face.", "– Le Chuck"); // Todo: code2str for monkey island quotes!

            ost << "<!DOCTYPE html>\r\n";
            ost << "<html>\r\n";
            ost << "<head>\r\n";
            ost << "<meta charset=\"UTF-8\" />\r\n";
            ost << "<title>";
            ost << code;
            ost << " ";
            ost << webserv::http::code2str(code);
            ost << "</title>\r\n";
            ost << "</head>\r\n";
            ost << "<body>\r\n";
            ost << "<h1>";
            ost << "Error at WebServ!";
            ost << "</h1>\r\n";
            ost << "<hr/>\r\n";
            ost << "<blockquote>\r\n";
            ost << "<p>";
            ost << quote.first;
            ost << "</p>\r\n";
            ost << quote.second;
            ost << "</blockquote>\r\n";
            ost << "<h3>";
            ost << code;
            ost << " ";
            ost << webserv::http::code2str(code);
            ost << "</h3>";
            ost << "</body>\r\n";
            ost << "</html>\r\n";

            response->set_code(code);
            response->set_html_body(ost.str());
        }

        void routing::permanent_redirect_301(webserv::http::response_fixed* response) {
            error_code(response, 301);
        }

        void routing::temporary_redirect_302(webserv::http::response_fixed* response) {
            error_code(response, 302);
        }

        void routing::bad_request_400(webserv::http::response_fixed* response) {
            error_code(response, 400);
        }

        void routing::unauthorized_401(webserv::http::response_fixed* response) {
            error_code(response, 401);
        }

        void routing::not_found_404(webserv::http::response_fixed* response) {
            error_code(response, 404);
        }

        void routing::gone_410(webserv::http::response_fixed* response) {
            error_code(response, 410);
        }

        void routing::teapot_418(webserv::http::response_fixed* response) {
            error_code(response, 418);
        }

        void routing::internal_server_error_500(webserv::http::response_fixed* response) {
            error_code(response, 500);
        }

        void routing::service_unavailable_503(webserv::http::response_fixed* response) {
            error_code(response, 503);
        }

        std::string routing::find_mime(std::string extension) {
            if (extension == ".bmp")
                return "image/bmp";
            else if (extension == ".css")
                return "text/css";
            else if (extension == ".csv")
                return "text/csv";
            else if (extension == ".doc")
                return "application/msword";
            else if (extension == ".docx")
                return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
            else if (extension == ".gif")
                return "image/gif";
            else if ((extension == ".html") || (extension == ".htm"))
                return "text/html";
            else if ((extension == ".jpeg") || (extension == ".jpg"))
                return "image/jpeg";
            else if (extension == ".js")
                return "text/javascript";
            else if (extension == ".json")
                return "application/json";
            else if (extension == ".png")
                return "image/png";
            else if (extension == ".pdf")
                return "application/pdf";
            else if (extension == ".php")
                return "application/x-httpd-php";
            else if (extension == ".txt")
                return "text/plain";
            else
                return "*/*";
        }

    } // namespace core
} // namespace webserv
