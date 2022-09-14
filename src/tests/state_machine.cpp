#include <iostream>
#include <memory>
#include <ctime>

#include "../http/state/a_cool_state_machine.hpp"

// #include "../http/state/state_machine.hpp"

struct screamer {
    screamer() { std::cout << "Creating screamer " << this << std::endl; }
    ~screamer() { std::cout << "Destroying screamer " << this << std::endl; }
};

void test_state_machine () {

    srand(time(0));

    std::cout << "Hello State Machine!\n" << std::endl;

    webserv::http::a_cool_state_machine    state_machine;

    // program loop goes here
    while (!state_machine.has_done()) {
        state_machine.update();
    }
}