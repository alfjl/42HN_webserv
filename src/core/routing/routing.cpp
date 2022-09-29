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
                    // is Datei oder nicht?
                    // Falls nein, machen wir directory listing
                    // (ALF) Check links in html!
                    if (get_instance().get_fs().open(file_path, stream)) {
                        std::ostringstream payload;
                        while (!stream.eof()) {
                            char c;
                            stream.get(c);
                            payload << c;
                        }
                        std::cout << "Done!" << std::endl;

                        response->set_code(200);
                        response->set_body(payload.str());
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

        void routing::error_code(webserv::http::response_fixed* response, unsigned int code) {
            std::ostringstream ost;
                
            std::pair<std::string, std::string> quote("Ah, there’s nothing like the hot winds of Hell blowing in your face.", "– Le Chuck"); // Todo: code2str for monkey island quotes!

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
            response->set_body(ost.str());
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

    } // namespace core
} // namespace webserv
