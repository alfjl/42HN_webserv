#include "defs.hpp"

#include "core/webservs.hpp"
#include "core/instance.hpp"
#include "config/config_parser.hpp"
#include "util/streamflow.hpp"

webserv::core::webservs  the_webserv;


void webserver_signal_handler(int signal) {
    (void) signal;
    the_webserv.interrupt();
}

void setup_interrupts() {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, webserver_signal_handler);
}

void webserv_main(const char* config_path) {
    webserv::util::fileflow flow(config_path);
    webserv::config::config_parser parser(flow, *the_webserv.new_instance());

    try {
        parser.run();
    } catch (webserv::util::parse_exception& e) {
        std::cout << "Unable to parse the config file!" << std::endl;
        return;
    }

    try {
        the_webserv.run();
    }
    catch (std::exception& e) {

    }

    std::cout << "Finished!" << std::endl;
}

void banner() {
    std::cout << std::endl;
    std::cout << "          T h e   W e b s e r v" << std::endl;
    std::cout << std::endl;
    std::cout << "    by alanghan@student.42heilbronn.de" << std::endl;
    std::cout << "       enijakow@student.42heilbronn.de" << std::endl;
    std::cout << "        nlenoch@student.42heilbronn.de" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: ./webserv <filename>" << std::endl;
        return 1;
    }
    banner();
    setup_interrupts();
    webserv_main(argv[1]);
    system("leaks webserv");
    return 0;
}
