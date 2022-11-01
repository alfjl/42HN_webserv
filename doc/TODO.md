ROUTING:
DONE - Move mimetype conversion function (find_mime) into a file with the HTTP error code mapping (code2str). possibly rename

PAL:
DONE - conv: add int_to_string (is currently implemented as itos() in routing)
DONE - guarded: probably not needed anymore
DONE - nullptr: probably not needed anymore
DONE - shared_ptr: superseded by refcounted, maybe adapt to that?
DONE - Ordner "dir" umbenennen, alle Dateioperationen in einen HPP+CPP packen (vielleicht "fs.hpp/.cpp"), Wrapper fuer ::close(int fd)
DONE - env: pwd() sollte keinen Path zurueckgeben, sondern einen std::string (der wird zwar spaeter in einen Path konvertiert, aber das hier ist erstmal nur das PAL und sollte nicht auf webserv::util zugreifen)
DONE - fork: Easypipe raus (und zu den Dateioperationen), fork()-Funktion verstecken (= aus dem Header rausnehmen), besseren Rueckgabewert und Error-Handling fuer fork_task.perform(), vor allem wenn das Programm nicht gefunden wurde (= execve failed sollte schon vor dem Fork gecheckt werden, mithilfe von pal::dir::access())
DONE - reactor: react_close() vielleicht umbenennen?
DONE - selector: beautify selector.select()
DONE - socket: Kommentare raus, fertig
DONE - pthread: Kann geloescht werden

TESTS:
DONE - Koennen raus

THREADING:
DONE - Kann raus

UTIL:
DONE - connection: Ist perfekt
DONE - iflow: Perfekt
DONE - notification: Kann raus?
DONE - oflow: Error handling
DONE - optional: zu PAL/cpp/
DONE - parser: eigene parse_exception werfen statt runtime_error
DONE - path: Perfekt
DONE - refcounted: Auch gut
DONE - state_machine: Methoden in state_machine.cpp auslagern (das Template ist weggefallen)
DONE - streamflow: Is da!
DONE - wrapped_queue: Perfekto!

HTTP_HEADERS:
DONE - In old/ oder doc/, Umwandlung von .cpp in .md oder .txt

HTTP:
DONE - uri: Methoden-"{ ... }" in uri.cpp verschieben (keine in HPP erlaubt)
DONE - response: For later, move code2str (see above: PAL)
DONE - request: Methoden-"{ ... }" in request.cpp verschieben (keine in HPP erlaubt)
DONE - fields: Perfekt, vielleicht Integer-Parsing einbauen (bool get(std::string key, int& value, int default_value))
 - request_parser: Refactoring, handle errors (e.g. unknown method names), handle URI encoding (e.g. %20 and other special chars) DO AS LAST POINT!!!
 - http_handler and cgi_handler: For later
DONE - EVERYTHING: move cgi_msg, request and response into one directory ("http/proto/"), rename request_core to request, rename cgi_msg to cgi_message


CORE:
 - instance: Perfekt, vielleicht Moeglichkeiten fuer mehrere gleichzeitige Server einbauen
 - component: Perfekt
 - scheduler: Perfekt, vielleicht spaeter Geschwindigkeitsoptimierung
 - filesystem: Spaeter hardgecodete Pfade ersetzen durch Werte aus der Config
 - driver: Perfekt
 - routing: Alles spaeter

CONFIG_PARSER:
 - Spaeter

MAIN:
 - Entschlacken

EXTRA:
DONE - Bugfix hängt bei fehlendem CGI programm/script (e.g. cgi5.cgi)


TODO:

config/config_parser.cpp: 
line 81 // TODO
refactoring

core/routing/pages.cpp:  
line 13 // todo: code2str for monkey island quotes!

core/routing/table/route.cpp: 
line 195-214 // comments

core/routing/table/route.hpp: 
line 103-109 // comments

core/routing/table/routing_table.cpp: 
line 7-8 // TODO: delete! test only!
line 42  // TODO, FIXME, XXX: This can lead to leaks

core/routing/routing.cpp: 
line 47 	// TODO, FIXME, XXX: Watch out for recursion! 
line 64 	// TODO: Does this always return false? 
line 67 	// Invisible yield
line 128	// /*, std::ios_base::out | std::ios_base::trunc)*/, outfile)) { // TODO: Add flags to write() 
line 132 	// if file couldn't be opened/constructed TODO: check against nginx/tester 
line 137 	// if file couldn't be opened/constructed TODO: check against nginx/tester
line 147    // TODO: This code exists merely to satisfy the second test case in the tester.
line 160 	// TODO: Check against nginx if this is correct behaviour!! Nginx: Allow to delete directories? Allow to recursively delete directories? 
line 175 	// TODO: Is there a better notation instead of '&(pointer->int)' 
line 197 	// communicate input and output to task 
line 200	// fork_task 
line 218	// TODO: Not needed anymore 
line 222	// TODO: Avoid the "return" in look_up: Call response->write() and give it a chance to write it out by itself 
line 287 	// comments

core/scheduler/scheduler.cpp: 
line 40 // TODO: Add to list of stopped handlers, remove elements later

http/handler/basic_handler.cpp: 
line 80, 99, 106, 121, 132 // returns do nothing
line 148 // TODO: Check how many bytes we have actually read
line 164 // TODO: Issue an error

http/handler/cgi_handler.cpp: 
line 80, 82 // comments
line 174 // TODO: This just puts memory pressure on the system - maybe write it out directly?

http/handler/http_handler.cpp:
line 31, 38, 77, 108, // comments

http/parsing/request_parser.cpp: 
line 5 	// #define EVIL 1 // TODO: Implement in comfig
lien 35 // FEATURE: Maybe add a configuration option to support combinations like "\n" as a newline as well? 
line 60 // TODO: Check for length 
line 105 // TODO: "?p1=v1&p2=v2" 
line 136 // TODO: Extract until space, then: parse_uri(the_text, line.get_uri()); 
line 78, 144-168, 198 // comments

http/proto/cgi_msg.cpp: 
line 37-53 // TODO: Needs to be parsed as well!
		   // TODO: localhost ?read out request field X-Forwarded-For?

http/proto/response.cpp: 
line 66 // TODO: Remove these later 
line 77-83 // comments

pal/cpp/conv.cpp: 
line 47 	// Properly check for invalid lines!

pal/env/env.cpp: 
line 3-13 	// 1. im Pal wrapper um getenv() returns std::string
    		// std::string pal::env::getenv(std::string)
   			// - NULL-check
   			// - .c_str()
   			// std::string pal::env::pwd()
   			//   return pal::env::getenv("PWD");
   			// webserv::util::path filesystem::pwd()
   			//    return path(pal::env::pwd())
   			// in add_anchor()
   			//    "/" + (pwd().cd("../www") + path).get_addr_s()
   			// in www folder alle nötigen files reinpacken aus dem tester
line 28-30  //    webserv::util::path pwd() {
			// 		return (webserv::util::path(getenv("PWD")));
			//    }

pal/env/env.hpp:
line 13 	// webserv::util::path pwd();

pal/fork/fork.cpp:
line 44		// NOTE: This ~wait_set should not be empty!
line 54		// TODO: Extract return code
line 114-115// if (!webserv::pal::fs::access(_executable) || (webserv::pal::fs::is_directory(_executable)))
            //    return false;

pal/net/selector.cpp:
line 40 	// TODO: call function on payload?
line 167 	// tv.tv_usec = 50000;
line 171 	// throw std::runtime_error("select(...) returned an error code!");

pal/net/selector.hpp:
line 24 	// socket = registered/active socket

pal/net/socket.cpp:
line 44 	// TODO: add setsockopt() for portability
line 116	// std::cout << "IP_address: " << client_connection.get_address_s() << " / uint32: " << client_connection.get_address_uint32() << " / PORT: " << client_connection.get_port() << std::endl;

util/state_machine.cpp:
line 28		// while (!return_stack.empty())
line 37 	// if (return_stack.empty()) {

util/state_machine.cpp:
line 35 	// std::stack<state_function>  return_stack;
line 60 	// return_stack.push(conv(func));
line 66		// return_stack.pop();