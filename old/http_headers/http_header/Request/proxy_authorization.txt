/* 

Contains credentials to authenticate user agent to proxy server, 
usually after server responded with 407 Proxy Authentication Required status & Proxy-Authenticate header.


SYNTAX:
Proxy-Authorization: <type> <credentials>

DIRECTIVES:
<type>
Authentication type. A common type is "Basic". See also the IANA registry of Authentication schemes.

<credentials>
Credentials are constructed like this:
Username & password are combined with colon (aladdin:opensesame).
Resulting string is base64 encoded (YWxhZGRpbjpvcGVuc2VzYW1l).

Note: Base64 encoding does not mean encryption or hashing! 
This method is as secure as sending the credentials in clear text (base64 is a reversible encoding). 
It is preferable to use HTTPS in conjunction with Basic Authentication.

EXAMPLES:
Proxy-Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l

*/