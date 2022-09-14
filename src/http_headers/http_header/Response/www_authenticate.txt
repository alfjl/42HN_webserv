/*

defines the HTTP authentication methods ("challenges") 
that might be used to gain access to a specific resource.

Server using HTTP authentication responds with 401 Unauthorized response to request for protected resource.
This response must include at least one WWW-Authenticate header and at least one challenge,
to indicate what authentication schemes can be used to access the resource 
(and any additional data that each particular scheme needs).

Multiple challenges are allowed in one WWW-Authenticate header,
and multiple WWW-Authenticate headers are allowed in one response.
A server may also include the WWW-Authenticate header in other response messages 
to indicate that supplying credentials might affect the response.

After receiving the WWW-Authenticate header,
a client will typically prompt the user for credentials,
and then re-request the resource.
This new request uses the Authorization header to supply the credentials to the server,
encoded appropriately for the selected "challenge" authentication method.
The client is expected to select the most secure of the challenges it understands 
(note that in some cases the "most secure" method is debatable).

SYNTAX:
At least one challenge must be specified. Multiple challenges may be specified, 
comma-separated, in a single header, or in individual headers:

// Challenges specified in single header
WWW-Authenticate: challenge1, ..., challengeN

// Challenges specified in multiple headers
WWW-Authenticate: challenge1
...
WWW-Authenticate: challengeN
A single challenge has the following format. Note that the scheme token (<auth-scheme>) is mandatory. 
The presence of realm, token68 and any other parameters depends on the definition of the selected scheme.

// Possible challenge formats (scheme dependent)
WWW-Authenticate: <auth-scheme>
WWW-Authenticate: <auth-scheme> realm=<realm>
WWW-Authenticate: <auth-scheme> token68
WWW-Authenticate: <auth-scheme> auth-param1=token1, ..., auth-paramN=auth-paramN-token
WWW-Authenticate: <auth-scheme> realm=<realm> token68
WWW-Authenticate: <auth-scheme> realm=<realm> token68 auth-param1=auth-param1-token , ..., auth-paramN=auth-paramN-token
WWW-Authenticate: <auth-scheme> realm=<realm> auth-param1=auth-param1-token, ..., auth-paramN=auth-paramN-token
WWW-Authenticate: <auth-scheme> token68 auth-param1=auth-param1-token, ..., auth-paramN=auth-paramN-token
For example, Basic authentication allows for optional realm and charset keys, but does not support token68.

WWW-Authenticate: Basic
WWW-Authenticate: Basic realm=<realm>
WWW-Authenticate: Basic realm=<realm>, charset="UTF-8"


DIRECTIVES:
<auth-scheme>
The Authentication scheme. Some of the more common types are (case-insensitive): Basic, Digest, Negotiate and AWS4-HMAC-SHA256.

Note: For more information/options see HTTP Authentication > Authentication schemes

realm=<realm> (Optional)
A string describing a protected area. A realm allows a server to partition up the areas it protects (if supported by a scheme that allows such partitioning),
 and informs users about which particular username/password are required. If no realm is specified, clients often display a formatted hostname instead.

<token68> (Optional)
A token that may be useful for some schemes. The token allows the 66 unreserved URI characters plus a few others. 
According to the specification, it can hold a base64, base64url, base32, or base16 (hex) encoding, with or without padding, but excluding whitespace.

Other than <auth-scheme> and the key realm, authorization parameters are specific to each authentication scheme. 
Generally you will need to check the relevant specifications for these (keys for a small subset of schemes are listed below).

Basic
<realm> (Optional)
As above.

charset="UTF-8" (Optional)
Tells the client the server's preferred encoding scheme when submitting a username and password. 
The only allowed value is the case-insensitive string "UTF-8". This does not relate to the encoding of the realm string.

Digest
<realm> (Optional)
String indicating which username/password to use. Minimally should include the host name, but might indicate the users or group that have access.

domain (Optional)
A quoted, space-separated list of URI prefixes that define all the locations where the authentication information may be used. 
If this key is not specified then the authentication information may be used anywhere on the web root.

nonce
A server-specified quoted string that the server can use to control the lifetime in which particular credentials will be considered valid.
This must be uniquely generated each time a 401 response is made, and may be regenerated more often (for example, allowing a digest to be used only once).
The specification contains advice on possible algorithms for generating this value. The nonce value is opaque to the client.

opaque
A server-specified quoted string that should be returned unchanged in the Authorization. 
This is opaque to the client. The server is recommended to include Base64 or hexadecimal data.

stale (Optional)
A case-insensitive flag indicating that the previous request from the client was rejected because the nonce used is too old (stale). 
If this is true the request can be re-tried using the same username/password encrypted using the new nonce. 
If it is any other value then the username/password are invalid and must be re-requested from the user.

algorithm (Optional)
Algorithm used to produce the digest. Valid non-session values are: "MD5" (default if not specified), "SHA-256", "SHA-512". 
Valid session values are: "MD5-sess", "SHA-256-sess", "SHA-512-sess".

qop
Quoted string indicating the quality of protection supported by the server. This must be supplied, and unrecognized options must be ignored.

"auth": Authentication
"auth-int": Authentication with integrity protection
charset="UTF-8" Optional
Tells the client the server's preferred encoding scheme when submitting a username and password. 
The only allowed value is the case-insensitive string "UTF-8".

userhash (Optional)
A server may specify "true" to indicate that it supports username hashing (default is "false")

EAMPLES:
Basic authentication
A server that only supports basic authentication might have a WWW-Authenticate response header which looks like this:

WWW-Authenticate: Basic realm="Access to the staging site", charset="UTF-8"
A user-agent receiving this header would first prompt the user for their username and password, and then re-request the resource: 
this time including the (encoded) credentials in the Authorization header. The Authorization header might look like this:

Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l
For "Basic" authentication the credentials are constructed by first combining the username and the password with a colon (aladdin:opensesame),
 and then by encoding the resulting string in base64 (YWxhZGRpbjpvcGVuc2VzYW1l).
*/