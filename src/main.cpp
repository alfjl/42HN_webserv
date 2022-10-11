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

void webserv_main() {
    webserv::core::instance  the_webserv;
    webserv::util::fileflow flow("../configs/test1.conf");
    webserv::config::config_parser parser(flow, the_webserv);

    parser.run();

    the_webserv.on_port(4242);
    the_webserv.run();
}

int main(int argc, char *argv[]) {
    webserv_main();
    return 0;
}
