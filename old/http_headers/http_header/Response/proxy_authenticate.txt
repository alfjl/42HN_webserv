/*

Defines authentication method that should be used to gain access to resource behind proxy server. 
Authenticates request to proxy server, allowing it to transmit request further.

Proxy-Authenticate header is sent along with a 407 Proxy Authentication Required.

SYNTAX:
Proxy-Authenticate: <type> realm=<realm>

DIRECTIVES:
<type>
Authentication type. A common type is "Basic". IANA maintains a list of authentication schemes.

realm=<realm>
A description of the protected area, the realm. If no realm is specified, clients often display a formatted host name instead.

EXAMPLES:
Proxy-Authenticate: Basic
Proxy-Authenticate: Basic realm="Access to the internal site"

*/