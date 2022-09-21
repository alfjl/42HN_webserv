/* 
Can provide credentials that authenticate a user agent with a server,
allowing access to protected resources.

Usually, but not always, sent after user agent attempts to request protected resource without credentials.
Server responds with '401 Unauthorized message' that includes min. 1 WWW-Authenticate header.
This header indicates the usable authentication schemes to access the resource 
(& any additional information the client needs to use them).
User-agent should select most secure authentication scheme supported from those offered, 
prompt user for their credentials, & re-request the resource 
(including the encoded credentials in the Authorization header).

SYNTAX:
Authorization: <auth-scheme> <authorization-parameters>

Basic authentication:
Authorization: Basic <credentials>

Digest authentication:
Authorization: Digest username=<username>,
    realm="<realm>",
    uri="<url>",
    algorithm=<algorithm>,
    nonce="<nonce>",
    nc=<nc>,
    cnonce="<cnonce>",
    qop=<qop>,
    response="<response>",
    opaque="<opaque>"

DIRECTIVES:
<auth-scheme>
The Authentication scheme that defines how the credentials are encoded.
Some of the more common types are (case-insensitive): Basic, Digest, Negotiate and AWS4-HMAC-SHA256.

Note: For more information/options see https://developer.mozilla.org/en-US/docs/Web/HTTP/Authentication#authentication_schemes

Other than <auth-scheme> the remaining directives are specific to each authentication scheme.
Generally needed to check relevant specifications for these (keys for a small subset of schemes are listed below).

BASIC
<credentials>
The credentials, encoded according to the specified scheme.

Note: For information about the encoding algorithm, see the examples: below, 
https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/WWW-Authenticate 
https://developer.mozilla.org/en-US/docs/Web/HTTP/Authentication, and in the relevant specifications.

DIGEST
<response>
String of the hex digits that proves that user knows a password. Algorithm encodes username & password,
 realm, cnonce, qop, nc, and so on. Described in detail in specification.

username
Quoted string containing user's name for specified realm in plain text or hash code in hexadecimal notation. 
If name contains unallowed characters in the field -> username* can be used instead (not "as well").

username*
User's name formatted using extended notation defined in RFC5987. 
Only be used if the name can't be encoded in username & if userhash is set "false".

uri
The Effective Request URI. 
See specification for more information.

realm
Realm of the requested username/password (again, should match the value in the corresponding 
https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/WWW-Authenticate response for the resource being requested).

opaque
Value in the corresponding https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/WWW-Authenticate
response for the resource being requested.

algorithm
Algorithm used to calculate digest. Algorithm must be supported from 
https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/WWW-Authenticate response for resource being requested.

qop
Token indicating the quality of protection applied to the message. Must match the one value in the set specified in 
https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/WWW-Authenticate response for the resource being requested.
"auth": Authentication
"auth-int": Authentication with integrity protection

cnonce
An quoted ASCII-only string value provided by the client. 
Used by client & server to provide mutual authentication, 
provide some message integrity protection, & avoid "chosen plaintext attacks". 
See specification for additional information.

nc
Nonce count. 
Hexadecimal count of requests in which client has sent the current cnonce value (including current request). 
Server uses duplicate nc values to recognize replay requests.

userhash (Optional)
"true" if username has been hashed. 
"false" by default.

EXAMPLES:
Basic authentication
"Basic" authentication constructs the credentials by combining first username & password with a colon (aladdin:opensesame),
& then encoding the resulting string in base64 (YWxhZGRpbjpvcGVuc2VzYW1l).
Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l

WARNING: 
Base64-encoding can easily be reversed to get original name & password -> Basic authentication is completely insecure. 
HTTPS is always recommended when using authentication, but is even more so when using Basic authentication.

See https://developer.mozilla.org/en-US/docs/Web/HTTP/Authentication for examples to 
configure Apache or Nginx servers to password protect your site with HTTP basic authentication.
*/