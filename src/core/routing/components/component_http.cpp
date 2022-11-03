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

    }
}
