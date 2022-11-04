#ifndef WEBSERV_HTTP_HANDLER_WRITING_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_WRITING_HANDLER_HPP

#include "../../defs.hpp"

#include "../../util/streamflow.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../parsing/request_parser.hpp"
#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class writing_handler : public basic_handler {
            std::string _text;            

        public:
            writing_handler(webserv::util::connection* connection, std::string text);
            ~writing_handler();

            
        };

    }
}

#endif
