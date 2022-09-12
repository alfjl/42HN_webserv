/* 

Server knows what to send to Client, the Client is addressing a file that is present on the Server.
The Client transmits a URL in the HTTP-Header to the Server.

SYNTAX: http://Servername.Domainname.Top-Level-Domain:TCP-Port/Pfad/Datei
EXAMPLE: http://www.elektronik-kompendium.de:80/sites/kom/0902231.htm

RULES:
Transfer-Protocol -> 'http://'
Servername (optional) -> 'www'
Domain-Name -> 'elektronik-kompendium' 
Top-Level-Domain (TLD) -> 'de'
TCP-Port (optional) (& only needed if different from standard Port 80) -> '80' can be from 0 to 65 535
Paths & Files are distinguised through the '/' 
(if no Path or File -> default-file is send)
(if Path &/ File exist -> send it back to client)
(if Path &/ File don't exist alternatives are tried -> if no success error 404)


*/

/* 
CODE

bool check_TP() {
	if (TP == 'http')
		return true;
	else
		return false;
}

bool check_serv() {
	if (serv == www)
		return true;
	else
		return fasle;
}

bool check_dname() {
	while (input[i] != '.') {
		dname = input[i];
		i++;
	}

	if (dname)
		return true;
	else
		return false; 
}

bool check_TLD() {
	while (input[i] != '.') {
		TLD = input[i];
		i++;
	}
	if (TLD)
		return true;
	else
		return false;
}

bool check_TCP() {
	if (TCP != 80)
		TCP needs to exists;
		if (TCP exists)
			return true;
		else
			return false;
	if (TCP == 80)
		return true;
}

// Check Path until file 
bool check_path() {
	if (path)
		return true;
	else
		return false;
}

// File hase a '.' in it
bool check_file() {
	if (file)
		return true;
	else
		return false;
}

if (check_TP() == true)
	TP = assign_TP();
if (check_serv == true)
	serv = assign_serv();
if (check_dname == true)
	dname = assign_dname();
if (check_TLD == true)
	TLD = assign_TLD();
if (check_TCP == true)
	TCP = assign_TCP();
if (check_path == true)
	path = assign_path();
if (check_file == true)
	file = assign_file();

if (check_TP() && check_Dname() && check_TLD())
	send(default);
else if (check_TP() && check_Dname() && check_TLD() && check_path())
	send(path);
else if (check_TP() && check_Dname() && check_TLD() && check_file())
	send(file);
else if (check_TP() && check_Dname() && check_TLD() && check_path() && check_file())
	send(path&file);
*/