#include "../http/parsing/request_parser.hpp"

void test_uri_parsing(std::string text, bool expected) {
    webserv::http::uri the_uri;

    bool res = webserv::http::parse_uri(text, the_uri);

    if (res == expected) {
        std::cout << "\033[32m";
    } else {
        std::cout << "\033[31m";
    }

    if (res) {
        std::cout << "\"" << text << "\" gets converted to " << the_uri << std::endl;
    } else {
        std::cout << "\"" << text << "\" is an error." << std::endl;
    }

    std::cout << "\033[0m";
}

void test_uri_parsing() {
    test_uri_parsing("httpx://www.42heilbronn.de:4242/index.html", true);
    test_uri_parsing("httpx://www.42heilbronn.de:4242x/index.html", false);
    test_uri_parsing("httpx://www.42heilbronn.de:42x42/index.html", false);
    test_uri_parsing("httpx://www.42heilbronn.de:x4242/index.html", false);

    test_uri_parsing("", false);
    test_uri_parsing("/", true);
    test_uri_parsing("/index", true);
    test_uri_parsing("/index/whatever/hallo", true);
    test_uri_parsing("/index/../whatever/hallo", true);
    test_uri_parsing("/index", true);
    test_uri_parsing("/index.html", true);
    test_uri_parsing(":42/", false);
    test_uri_parsing("42/", false);  // Is this really correct?
    test_uri_parsing("42.fr", true);

    webserv::http::path anchor("/var/www");
    webserv::http::path resource("/img/favicon.png");

    std::cout << (anchor + resource) << std::endl;
    std::cout << (anchor + resource).get_first() << std::endl;
    std::cout << (anchor + resource).get_last() << std::endl;
    std::cout << (anchor + resource).get_rest() << std::endl;
}
