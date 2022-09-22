/*

Added by proxies, both forward and reverse, and can appear in the request or response headers. 
Used for tracking message forwards, avoiding request loops, & identifying protocol capabilities of senders along request/response chain.

SYNTAX:
Via: [ <protocol-name> "/" ] <protocol-version> <host> [ ":" <port> ]
Via: [ <protocol-name> "/" ] <protocol-version> <pseudonym>

DIRECTIVES:
<protocol-name>
Optional. The name of the protocol used, such as "HTTP".

<protocol-version>
The version of the protocol used, such as "1.1".

<host> and <port>
Public proxy URL and port.

<pseudonym>
Name/alias of an internal proxy.

EXAMPLES:
Via: 1.1 vegur
Via: HTTP/1.1 GWA
Via: 1.0 fred, 1.1 p.example.net
*/