#include "../util/streamflow.hpp"

/* 
Template fungiert als Platzhalter hier stringflow oder fileflow
void test bekommt ein argument hier Hello
Template T ist was in test< >() eingesetzt wird
webserv::util::streamflow wrappet welcher stream (stringflow oder fileflow) umwandelt
next_char returnes a bool & uses a char& location, daher geben wir den char c aus
*/
template<typename T>
void test(std::string arg) {
	T  stream(arg);
	webserv::util::streamflow  flow(stream);

	char c;

	while (!flow.next_char(c)) {
		std::cout << c;
	}

	while (flow.has_next() == true) {
		std::cout << c;
		c = flow.force_next_char();
	}

}

void test_streamflow() {
	// std::stringstream          stream("Helloe!");
	// webserv::util::streamflow  flow(stream);


	// webserv::util::stringflow flow("Helloe!");
	// webserv::util::fileflow   fflow("./test.txt");

	// char c;

	// while (!next_char(c)) {
	// 	std::cout << c;
	// }



	// test<webserv::util::stringflow>("Hello");
	// test<webserv::util::fileflow>("./test.txt");
}
