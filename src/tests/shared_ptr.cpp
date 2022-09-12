// wrap_shared example
#include <iostream>
#include <memory>

#include "../pal/cpp/shared_ptr.hpp"

struct screamer {
    screamer() { std::cout << "Creating screamer " << this << std::endl; }
    ~screamer() { std::cout << "Destroying screamer " << this << std::endl; }
};

void test_shared_ptr () {

    webserv::pal::cpp::shared_ptr<int> foo = webserv::pal::cpp::wrap_shared<int>(new int(10) );
    // same as:
    webserv::pal::cpp::shared_ptr<int> foo2 (new int(10));

    webserv::pal::cpp::shared_ptr<int> bar = webserv::pal::cpp::wrap_shared<int> (new int(20));

    webserv::pal::cpp::shared_ptr<std::pair<int,int> > baz = webserv::pal::cpp::wrap_shared<std::pair<int,int> > (new std::pair<int, int>(30,40));

    std::cout << "*foo: " << *foo << '\n';
    std::cout << "*bar: " << *bar << '\n';
    std::cout << "*baz: " << baz->first << ' ' << baz->second << '\n';

    webserv::pal::cpp::shared_ptr<screamer> ptr = webserv::pal::cpp::wrap_shared<screamer>(new screamer);
    {
        webserv::pal::cpp::shared_ptr<screamer> ptr2 = ptr;
        ptr = webserv::pal::cpp::wrap_shared<screamer>(new screamer);
    }

}