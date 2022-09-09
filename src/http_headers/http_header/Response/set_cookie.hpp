/*

Used to send cookie from server to user agent, so that user agent can send it back to server later. 
To send multiple cookies, multiple Set-Cookie headers should be sent in same response.

Warning: Browsers block frontend JavaScript code from accessing the Set-Cookie header, as required by the Fetch spec, 
which defines Set-Cookie as a forbidden response-header name that must be filtered out from any response exposed to frontend code.

For more information, see the guide https://developer.mozilla.org/en-US/docs/Web/HTTP/Cookies.

SYNTAX:
Set-Cookie: <cookie-name>=<cookie-value>
Set-Cookie: <cookie-name>=<cookie-value>; Expires=<date>
Set-Cookie: <cookie-name>=<cookie-value>; Max-Age=<number>
Set-Cookie: <cookie-name>=<cookie-value>; Domain=<domain-value>
Set-Cookie: <cookie-name>=<cookie-value>; Path=<path-value>
Set-Cookie: <cookie-name>=<cookie-value>; Secure
Set-Cookie: <cookie-name>=<cookie-value>; HttpOnly

Set-Cookie: <cookie-name>=<cookie-value>; SameSite=Strict
Set-Cookie: <cookie-name>=<cookie-value>; SameSite=Lax
Set-Cookie: <cookie-name>=<cookie-value>; SameSite=None; Secure

// Multiple attributes are also possible, for example:
Set-Cookie: <cookie-name>=<cookie-value>; Domain=<domain-value>; Secure; HttpOnly

Attributes
<cookie-name>=<cookie-value>
Defines the cookie name and its value. A cookie definition begins with a name-value pair.

A <cookie-name> can contain any US-ASCII characters except for: the control character, space, or a tab.
It also must not contain separator characters like the following: ( ) < > @ , ; : \ " / [ ] ? = { }.

A <cookie-value> can optionally be wrapped in double quotes and include any US-ASCII character excluding: 
control character, Whitespace, double quotes, comma, semicolon, and backslash.

Encoding: Many implementations perform URL encoding on cookie values. However, this is not required by the RFC specification. 
The URL encoding does help to satisfy the requirements of the characters allowed for <cookie-value>.

Expires=<date> (Optional)
Indicates the maximum lifetime of the cookie as an HTTP-date timestamp. See Date for the required formatting.

If unspecified, the cookie becomes a session cookie. A session finishes when the client shuts down, after which the session cookie is removed.

When an Expires date is set, the deadline is relative to the client the cookie is being set on, not the server.

Max-Age=<number> (Optional)
Indicates the number of seconds until the cookie expires. A zero or negative number will expire the cookie immediately. 
If both Expires and Max-Age are set, Max-Age has precedence.

Domain=<domain-value> (Optional)
Defines the host to which the cookie will be sent.

If omitted, this attribute defaults to the host of the current document URL, not including subdomains.

Contrary to earlier specifications, leading dots in domain names (.example.com) are ignored.

Multiple host/domain values are not allowed, but if a domain is specified, then subdomains are always included.

Path=<path-value> (Optional)
Indicates the path that must exist in the requested URL for the browser to send the Cookie header.

The forward slash (/) character is interpreted as a directory separator, and subdirectories are matched as well. For example, for Path=/docs,

the request paths /docs, /docs/, /docs/Web/, and /docs/Web/HTTP will all match.
the request paths /, /docsets, /fr/docs will not match.
Secure Optional
Indicates that the cookie is sent to the server only when a request is made with the https: 
scheme (except on localhost), and therefore, is more resistant to man-in-the-middle attacks.

HttpOnly (Optional)
Forbids JavaScript from accessing the cookie, for example, through the Document.cookie property. 
Note that a cookie that has been created with HttpOnly will still be sent with JavaScript-initiated requests, 
e.g. when calling XMLHttpRequest.send() or fetch(). This mitigates attacks against cross-site scripting (XSS).

SameSite=<samesite-value> (Optional)
Controls whether or not a cookie is sent with cross-site requests, providing some protection against cross-site request forgery attacks (CSRF).

The possible attribute values are:

Strict
means that the browser sends the cookie only for same-site requests, that is, requests originating from the same site that set the cookie. 
If a request originates from a different domain or scheme (even with the same domain), no cookies with the SameSite=Strict attribute are sent.

Lax
means that the cookie is not sent on cross-site requests, such as on requests to load images or frames, 
but is sent when a user is navigating to the origin site from an external site (for example, when following a link). 
This is the default behavior if the SameSite attribute is not specified.

None
means that the browser sends the cookie with both cross-site and same-site requests. 
The Secure attribute must also be set when setting this value, like so SameSite=None; Secure

EXAMPLES:
Session cookie
Session cookies are removed when the client shuts down. Cookies are session cookies if they do not specify the Expires or Max-Age attribute.

Set-Cookie: sessionId=38afes7a8
Permanent cookie
Permanent cookies are removed at a specific date (Expires) or after a specific length of time (Max-Age) and not when the client is closed.

Set-Cookie: id=a3fWa; Expires=Wed, 21 Oct 2015 07:28:00 GMT
Set-Cookie: id=a3fWa; Max-Age=2592000
Invalid domains
A cookie for a domain that does not include the server that set it should be rejected by the user agent.

The following cookie will be rejected if set by a server hosted on originalcompany.com:

Set-Cookie: qwerty=219ffwef9w0f; Domain=somecompany.co.uk
A cookie for a subdomain of the serving domain will be rejected.

The following cookie will be rejected if set by a server hosted on example.com:

Set-Cookie: sessionId=e8bb43229de9; Domain=foo.example.com

*/

