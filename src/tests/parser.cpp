#include "../http/parsing/request_parser.hpp"

void test_uri_parsing(std::string text) {
    webserv::http::uri the_uri;

    if (webserv::http::parse_uri(text, the_uri)) {
        std::cout << "\"" << text << "\" gets converted to " << the_uri << std::endl;
    } else {
        std::cout << "\"" << text << "\" is an error." << std::endl;
    }
}

void test_uri_parsing() {
    test_uri_parsing("httpx://www.42heilbronn.de:4242/index.html");
    test_uri_parsing("httpx://www.42heilbronn.de:4242x/index.html");
    test_uri_parsing("httpx://www.42heilbronn.de:42x42/index.html");
    test_uri_parsing("httpx://www.42heilbronn.de:x4242/index.html");
}
