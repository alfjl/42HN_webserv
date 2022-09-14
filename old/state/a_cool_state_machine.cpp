#include "a_cool_state_machine.hpp"
#include "cool_states.hpp"

webserv::http::a_cool_state_machine::a_cool_state_machine() {
    m_start_state = new start_state();
    m_state1 = new state1();
    m_state2 = new state2();
    m_stateN = new stateN();
    state_machine<a_cool_state_machine>::init(this, m_start_state);
    std::cout << "a_cool_state_machine created!" << std::endl;
}

webserv::http::a_cool_state_machine::~a_cool_state_machine() {
    delete m_start_state;
    delete m_state1;
    delete m_state2;
    delete m_stateN;
    std::cout << "a_cool_state_machine destroyed!" << std::endl;
}

void webserv::http::a_cool_state_machine::update() {
    state_machine<a_cool_state_machine>::update();
}
