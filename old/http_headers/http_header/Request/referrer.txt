/* 

Contains absolute or partial address of page makeing the request. 
Allows server to identify page where people are visiting from. 
Data can be used for analytics, logging, optimized caching, & more.

If following a link, Referer contains address of page that owns the link.
If makeing resource requests to another domain, Referer contains address of page that uses the requested resource.

Can contain origin, path, & querystring, & may not contain URL fragments (i.e. "#section") or "username:password" information. 
Request's referrer policy defines data that can be included. See Referrer-Policy for more information & examples.

Note: The header name "referer" is actually a misspelling of the word "referrer". See HTTP referer on Wikipedia for more details.

SYNTAX:
Referer: <url>

DIRECTIVES:
<url>
An absolute or partial address of the web page that makes the request. URL fragments (i.e. "#section") and userinfo (i.e. "username:password" in "https://username:password@example.com/foo/bar/") are not included. Origin, path, and querystring may be included, depending on the referrer policy.

EXAMPLES:
Referer: https://developer.mozilla.org/en-US/docs/Web/JavaScript
Referer: https://example.com/page?q=123
Referer: https://example.com/

*/