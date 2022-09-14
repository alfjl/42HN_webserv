/*

indicates how long the user agent should wait before making a follow-up request. There are three main cases this header is used:

If 503 (Service Unavailable) response, indicates how long service is expected to be unavailable.
If 429 (Too Many Requests) response, indicates how long to wait before making a new request.
If redirect response, such as 301 (Moved Permanently), indicates minimum time that user agent needs to wait before issuing redirected request.

SYNTAX:
Retry-After: <http-date>
Retry-After: <delay-seconds>

DIRECTIVES:
<http-date>
A date after which to retry. See the Date header for more details on the HTTP date format.

<delay-seconds>
A non-negative decimal integer indicating the seconds to delay after the response is received.

EXAMPLES:
Dealing with scheduled downtime
Support for the Retry-After header on both clients and servers is still inconsistent. 
However, some crawlers and spiders, like the Googlebot, honor the Retry-After header. 
Useful to send along with 503 (Service Unavailable) response, that search engines keep indexing site when downtime is over.

Retry-After: Wed, 21 Oct 2015 07:28:00 GMT
Retry-After: 120

*/