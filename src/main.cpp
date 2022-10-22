#include "defs.hpp"

#include "core/instance.hpp"
#include "config/config_parser.hpp"
#include "util/streamflow.hpp"

webserv::core::instance  the_webserv;

void webserver_signal_handler(int signal) {
    the_webserv.interrupt();
}

void setup_interrupts() {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, webserver_signal_handler);
}

void webserv_main(const char* config_path) {
    webserv::util::fileflow flow(config_path);
    webserv::config::config_parser parser(flow, the_webserv);

    try {
        parser.run();
    } catch (webserv::util::parse_exception& e) {
        std::cout << "Unable to parse the config file!" << std::endl;
        return;
    }

    the_webserv.run();

    std::cout << "Finished!" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: ./webserv <filename>" << std::endl;
        return 1;
    }
    setup_interrupts();
    webserv_main(argv[1]);
    system("leaks webserv");
    return 0;
}
