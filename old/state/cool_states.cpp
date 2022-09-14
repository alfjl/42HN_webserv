#include "cool_states.hpp"
#include "event_generator.hpp"
#include "a_cool_state_machine.hpp"

void webserv::http::start_state::Execute(a_cool_state_machine *pOwner) {
    std::cout << "start_state: executing..!" << std::endl;
    // at the beginning, we are in this start state
    // we are waiting for an event to occur, so we can jump into state1
    if (webserv::http::event_generator::get_instance()->generate(1)) {
        // here the event has occured
        pOwner->change_state(pOwner->m_state1);
    }
}

void webserv::http::state1::Execute(a_cool_state_machine *pOwner) {
    std::cout << "state1: executing..!" << std::endl;
    // at state1 we are waiting for 2 events
    // one for jumping to state2
    // and another is for jumping to stateN
    int event = webserv::http::event_generator::get_instance()->generate(2);
    if (event == 2) {
        // here the event has occured
        pOwner->change_state(pOwner->m_state2);
    }
    else if (event == 1) {
        pOwner->change_state(pOwner->m_stateN);
    }
}

void webserv::http::state2::Execute(a_cool_state_machine *pOwner) {
    std::cout << "state2: executing..!" << std::endl;
    // at state2 when the event occurs,
    // we jump back to state1
    if (webserv::http::event_generator::get_instance()->generate(1)) {
        //here the event has occured
        pOwner->change_state(pOwner->m_state1);
    }
}

void webserv::http::stateN::Execute(a_cool_state_machine *pOwner) {
    // and finally when we reach this state,
    // the program is terminated,
    // and we don't go anywhere

    // let's signal this event out, so that the program can terminate
    pOwner->done();
    std::cout << "stateN: terminated!" << std::endl;
}