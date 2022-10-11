#include "defs.hpp"

#include "core/instance.hpp"
#include "config/config_parser.hpp"
#include "util/streamflow.hpp"

void test_sockets();
void test_uri_parsing();

void test_all() {
    std::cout << "\nHello, 42 world!" << std::endl;
    std::cout << "\n --------- SOCKETS --------- \n" << std::endl;
    test_sockets();
    std::cout << "\n --------- URI PARSING --------- \n" << std::endl;
    test_uri_parsing();
}

void setup_interrupts() {
    signal(SIGPIPE, SIG_IGN);
}

void webserv_main(const char* config_path) {
    webserv::core::instance  the_webserv;
    webserv::util::fileflow flow(config_path);
    webserv::config::config_parser parser(flow, the_webserv);

    try {
        parser.run();
    } catch (std::runtime_error& e) {
        std::cout << "Unable to parse the config file!" << std::endl;
        return;
    }

    the_webserv.run();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: ./webserv <filename>" << std::endl;
        return 1;
    }
    webserv_main(argv[1]);
    return 0;
}
