/* 

Contains date/time after which response is considered expired.

Invalid expiration dates with value 0 represent date in the past & mean that resource is already expired.

If there is Cache-Control header with the max-age or s-maxage directive in the response, the Expires header is ignored.

SYNTAX:
Expires: <http-date>

DIRECTIVES:
<http-date>
An HTTP-date timestamp.

EXAMPLES:
Expires: Wed, 21 Oct 2015 07:28:00 GMT

*/