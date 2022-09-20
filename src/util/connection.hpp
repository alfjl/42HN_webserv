#ifndef WEBSERV_UTIL_CONNECTION_HPP
#define WEBSERV_UTIL_CONNECTION_HPP

#include "../defs.hpp"

#include "iflow.hpp"
#include "wrapped_queue.hpp"
#include "../pal/net/reactor.hpp"

namespace webserv {
    namespace util {

        class connection : public webserv::pal::net::reactor {
        private:
            wrapped_queue     input_buffer;
            wrapped_queue     output_buffer;
            bool              closed;

        public:
            connection();

            wrapped_queue& get_input();
            wrapped_queue& get_output();

            void close();
            bool is_closed();

            void react_close();

        }; // class connection

    } // namespace util
} // namespace webserv

#endif