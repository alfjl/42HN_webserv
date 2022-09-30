#ifndef WEBSERV_UTIL_CONNECTION_HPP
#define WEBSERV_UTIL_CONNECTION_HPP

#include "../defs.hpp"

#include "../pal/net/reactor.hpp"

#include "iflow.hpp"
#include "oflow.hpp"
#include "wrapped_queue.hpp"

namespace webserv {
    namespace util {

        class connection : public webserv::pal::net::reactor {
            oflow             out;
            std::ostream      ostream;
            wrapped_queue     input_buffer;
            wrapped_queue     output_buffer;
            bool              closed;

        public:
            connection();

            wrapped_queue& get_input();
            wrapped_queue& get_output();
            std::ostream&  get_ostream();

            void close();
            bool is_closed();

            void react_close();
        };

    }
}

#endif
