#include "event_generator.hpp"

webserv::http::event_generator *webserv::http::event_generator::get_instance() {
    static event_generator  s_instance;
    return &s_instance;
}

int     webserv::http::event_generator::generate(int eventNum) {
    if (m_counter == 0) {
        m_counter = rand() % MAX_COUNTER + 1;
        if (eventNum > 1)
            return (rand() % eventNum + 1);
        return 1;
    }
    else {
        m_counter--;
    }
    return 0;
}