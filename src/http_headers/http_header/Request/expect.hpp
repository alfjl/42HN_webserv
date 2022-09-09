/* 

Indicates expectations needed by server to handle request successfully.

Upon Expect: 100-continue, server responds:

100 (Continue) if information from request header is sufficient to cause immediate success
417 (Expectation Failed) if server cannot meet expectation
or any other 4xx status otherwise.

E.g. server may reject request if its Content-Length is too large.

No common browsers send this header, but some clients like cURL do so by default.

SYNTAX:
Expect: 100-continue

DIRECTIVES:
Only 1 defined expectation:

100-continue
Informs recipients that client is about to send a (presumably large) message body 
in this request & wishes to receive a 100 (Continue) interim response.

EXAMPLES:
Large message body
Client sends request with this header & waits for server to respond before sending message body.

PUT /somewhere/fun HTTP/1.1
Host: origin.example.com
Content-Type: video/h264
Content-Length: 1234567890987
Expect: 100-continue

Server checks headers & generates response. Server sends 100 (Continue) -> instructs client to send message body.

*/