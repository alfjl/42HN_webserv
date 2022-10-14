#include "http_handler.hpp"

#include "../../core/routing/routing.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"
#include "../response.hpp"

namespace webserv {
    namespace http {

        http_handler::http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing)
            : basic_handler(new_connection), _routing(routing) {
                
        }

        http_handler::~http_handler() {

        }

        void http_handler::fall_asleep() {
            // TODO: Implement!
        }     

        void http_handler::wake_up() {
            // TODO: Implement!
        }

    }
}
