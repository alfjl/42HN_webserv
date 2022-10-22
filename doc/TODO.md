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
 - selector: beautify selector.select()
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
 - oflow: Error handling
 - optional: zu PAL/cpp/
 - parser: eigene parse_exception werfen statt runtime_error
 - path: Perfekt
 - refcounted: Auch gut
 - state_machine: Methoden in state_machine.cpp auslagern (das Template ist weggefallen)
 - streamflow: Is da!
 - wrapped_queue: Perfekto!

HTTP_HEADERS:
DONE - In old/ oder doc/, Umwandlung von .cpp in .md oder .txt

HTTP:
 - uri: Methoden-"{ ... }" in uri.cpp verschieben (keine in HPP erlaubt)
 - response: For later, move code2str (see above: PAL)
 - request: Methoden-"{ ... }" in request.cpp verschieben (keine in HPP erlaubt)
 - fields: Perfekt, vielleicht Integer-Parsing einbauen (bool get(std::string key, int& value, int default_value))
 - request_parser: Refactoring, handle errors (e.g. unknown method names), handle URI encoding (e.g. %20 and other special chars) DO AS LAST POINT!!!
 - http_handler and cgi_handler: For later
 - EVERYTHING: move cgi_msg, request and response into one directory ("http/proto/"), rename request_core to request, rename cgi_msg to cgi_message


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
 - Bugfix hängt bei fehlendem CGI programm/script (e.g. cgi5.cgi)
