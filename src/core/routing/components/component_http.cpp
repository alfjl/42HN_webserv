#include "../../instance.hpp"

#include "../cgi/cgi.hpp"
#include "../pages/pages.hpp"

#include "component_http.hpp"


namespace webserv {
    namespace core {

        routing_component_http::routing_component_http(routing& routing) : routing_component(routing) {
            
        }


        void routing_component_http::handle_head(route& route) {
            handle_get(route);
            get_response().block_body();
        }

        void routing_component_http::handle_get(route& route) {
            webserv::util::path file_path = route.get_file_target();
            std::ifstream stream;
                    
            if (get_instance().get_fs().is_directory(file_path)) {
                if (route.is_directory_listing_on())
                    directory_listing(get_response(), get_instance().get_fs().read_absolute_path(file_path));
                else if (route.is_added_path_on()) {
                    if (get_instance().get_fs().open(file_path + route.get_added_path().value(), stream))
                        file_listing(get_response(), file_path + route.get_added_path().value(), &stream);
                    else
                        internal_server_error_500(get_response());
                } else
                    not_found_404(get_response());
            } else if (get_instance().get_fs().open(file_path, stream)) {
                file_listing(get_response(), file_path, &stream);
            } else {
                not_found_404(get_response());
            }
        }

        void routing_component_http::process_post_body(webserv::util::path file_path) {
             std::ofstream outfile;

            if (get_instance().get_fs().write(file_path/*, std::ios_base::out | std::ios_base::trunc)*/, outfile)) { // TODO: Add flags to write()
                outfile << get_request().get_body().c_str();

                if (!outfile.good())
                    internal_server_error_500(get_response()); // if file couldn't be opened/constructed TODO: check against nginx/tester
                outfile.close();

                get_response().set_html_body(get_request().get_body());
            } else {
                internal_server_error_500(get_response()); // if file couldn't be opened/constructed TODO: check against nginx/tester
            }
        }

        void routing_component_http::handle_post(route& route) {
            webserv::util::path file_path = route.get_file_target();

            get_response().set_code(get_instance().get_fs().accessible(file_path) ? 200 : 201);
            
            if (get_instance().get_fs().is_directory(file_path)) {
                // TODO: This code exists merely to satisfy the second test case in the tester.
                method_not_allowed_405(get_response());
            } else {
                process_post_body(file_path);
            }
        }


        void routing_component_http::handle_delete(route& route) {
            webserv::util::path file_path = route.get_file_target();
            std::ifstream stream;

            if (get_instance().get_fs().is_directory(file_path)) {  // TODO: Check against nginx if this is correct behaviour!! Nginx: Allow to delete directories? Allow to recursively delete directories?
                if (!get_instance().get_fs().del(file_path))
                    unauthorized_401(get_response());
            } else if ((get_instance().get_fs().del(file_path))) {
                set_delete_response(get_response());
            } else {
                not_found_404(get_response());
            }
        }

    }
}
