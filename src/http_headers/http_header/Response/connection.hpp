/* 

Controls if network connection stays open after current transaction finishes. 
If value sent is keep-alive, connection is persistent & not closed, 
allowing for subsequent requests to the same server.

Except for standard hop-by-hop headers 
(Keep-Alive, Transfer-Encoding, TE, Connection, Trailer, Upgrade, Proxy-Authorization & Proxy-Authenticate), 
any hop-by-hop headers used by message must be listed in Connection header, 
so that first proxy knows it has to consume them & not forward them further. 
Standard hop-by-hop headers are also required to be listed.

SYNTAX:
Connection: keep-alive
Connection: close

DIRECTIVES:
close
Indicates either client or server want to close connection. Default on HTTP/1.0 requests.

Comma-separated list of HTTP headers [Usually keep-alive only]
Indicates that client want to keep the connection open. 
Keeping a connection open is default on HTTP/1.1 requests. 
List of headers are the name of the header to be removed by first non-transparent proxy or cache in-between: 
these headers define connection between emitter & first entity, not the destination node.

*/