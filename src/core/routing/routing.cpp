#include "routing.hpp"

#include "routing_table.hpp"
#include "../instance.hpp"

namespace webserv {
    namespace core {

        routing::routing(instance& the_inst) : component(the_inst) {

        }

        routing::~routing() {

        }

        webserv::http::response* routing::look_up(webserv::http::request_core& request) {
            webserv::http::response *response = new webserv::http::response();

            switch (request.get_line().get_method()) {
                // case webserv::http::http_method_options: std::cout << "TODO: case http_method_options:" << std::endl; break;
                case webserv::http::http_method_get: {
                    webserv::core::routing_table table;
                    webserv::util::path file_path = table.query(request.get_line().get_uri().get_path());
                    std::ifstream stream;
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
                        response->set_code(404);
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
                    response->set_code(404);
                    response->set_body("<html><head></head><body>Error 404!</body></html>");
                    break;
                }
            }
            return (response);
        }

        void routing::tick() {
            // Do nothing!
        }

    } // namespace core
} // namespace webserv
