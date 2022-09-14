#ifndef WEBSERV_HTTP_STATE_EVENT_GENERATOR_HPP
#define WEBSERV_HTTP_STATE_EVENT_GENERATOR_HPP

#include "../../defs.hpp"

#define MAX_COUNTER 5

namespace webserv {
    namespace http {

        class event_generator {

        private:
            int     m_counter;
            event_generator() {
                m_counter = rand() % MAX_COUNTER + 1;
            }

        public:
            // this class is a singleton // = Concept NEEDS to be changed!
            static  event_generator *get_instance();
            void    clean_up() {}

            int     generate(int eventNum);

        }; // class event_generator

    } // namespace http
} // namespace webserve

#endif
