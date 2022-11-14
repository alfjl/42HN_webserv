#include "../../instance.hpp"

#include "../pages/pages.hpp"

#include "component_http.hpp"


namespace webserv {
    namespace core {

        static std::string generate_cookie_string() {
            std::string s;

            for (int x = 0; x < 32; x++) {
                s += "0123456789abcdef"[rand() % 16];
            }

            return s;
        }


        routing_component_http::routing_component_http(routing& routing) : routing_component(routing) {
            
        }


        void routing_component_http::handle_head(route& route) {
            handle_get(route);
            get_response().block_body();
        }

        void routing_component_http::handle_get(route& route) {
            webserv::util::path file_path = route.get_file_target();
            std::ifstream stream;

            if (!get_parent().get_request().get_fields().has("Cookie"))
                get_parent().get_response().set_field("Set-Cookie", generate_cookie_string());
                    
            if (get_instance().get_fs().is_directory(file_path)) {
                if (route.is_directory_listing_on())
                    directory_listing(get_response(), get_instance().get_fs().read_absolute_path(file_path));
                else if (route.is_added_path_on()) {
                    if (get_instance().get_fs().open(file_path + route.get_added_path().value(), stream))
                        file_listing(get_response(), file_path + route.get_added_path().value(), stream);
                    else
                        get_parent().get_component_pages().error_page(500);
                } else
                    get_parent().get_component_pages().error_page(404);
            } else if (get_instance().get_fs().open(file_path, stream)) {
                file_listing(get_response(), file_path, stream);
            } else {
                get_parent().get_component_pages().error_page(404);
            }
        }

        void routing_component_http::process_post_body(webserv::util::path file_path) {
             std::ofstream outfile;

            if (get_instance().get_fs().write(file_path/*, std::ios_base::out | std::ios_base::trunc)*/, outfile)) { // TODO: Add flags to write()
                get_request().get_body().write_to_stream(outfile);

                if (!outfile.good())
                    get_parent().get_component_pages().error_page(500); // if file couldn't be opened/constructed TODO: check against nginx/tester
                outfile.close();

                get_response().set_html_body(get_request().get_body().to_string());  // XXX
            } else {
                get_parent().get_component_pages().error_page(500); // if file couldn't be opened/constructed TODO: check against nginx/tester
            }
        }

        void routing_component_http::handle_post(route& route) {
            webserv::util::path file_path = route.get_file_target();

            get_response().set_code(get_instance().get_fs().accessible(file_path) ? 200 : 201);
            
            if (get_instance().get_fs().is_directory(file_path))
                get_parent().get_component_pages().error_page(405);
            else
                process_post_body(file_path);
        }


        void routing_component_http::handle_delete(route& route) {
            webserv::util::path file_path = route.get_file_target();
            std::ifstream stream;

            if (get_instance().get_fs().is_directory(file_path))
                get_parent().get_component_pages().error_page(401);
            else if ((get_instance().get_fs().del(file_path)))
                set_delete_response(get_response());
            else
                get_parent().get_component_pages().error_page(404);
        }

    }
}
