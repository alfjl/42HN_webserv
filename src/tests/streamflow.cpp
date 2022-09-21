#include "../util/streamflow.hpp"

void test_streamflow() {
	
	webserv::util::fileflow   flow("./tests/testfiles/test82.txt");

	char c;

	while (!flow.next_char(c)) {
		std::cout << c;
	}

	while (flow.has_next() == true) {
		std::cout << c;
		c = flow.force_next_char();
	}

}
