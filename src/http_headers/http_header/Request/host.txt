/* 

Specifies host & port number of server to which request is sent.

If no port is included, default port for service requested is implied (e.g., 443 for HTTPS URL, and 80 for HTTP URL).

Host header field must be sent in all HTTP/1.1 request messages. 
400 (Bad Request) status code may be sent to any HTTP/1.1 request message lacking or containing more than 1 Host header field.

SYNTAX:
Host: <host>:<port>

DIRECTIVES:
<host>
Domain name of server (for virtual hosting).

<port> (Optional)
TCP port number where server is listening.

EXAMPLES
Host: developer.mozilla.org

*/