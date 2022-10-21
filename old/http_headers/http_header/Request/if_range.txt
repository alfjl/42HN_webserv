/* 

Makes range request conditional: 
If condition is fulfilled, range request is issued, & server sends 206 Partial Content answer with appropriate body. 
If condition is not met, full resource is sent back with 200 OK status.

Can be used either with Last-Modified validator or with ETag, but not with both.

Most common use case: resume download -> guarantees stored resource wasn't modified since last fragment was received.

SYNTAX:
If-Range: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT
If-Range: <etag>

DIRECTIVES:
<etag>
Entity tag uniquely represents requested resource. String of ASCII characters in double quotes (Like "675af34563dc-tr34"). 
Weak entity tag (one prefixed by W/) must not be used in this header.

<day-name>
One of "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", or "Sun" (case-sensitive).

<day>
2 digit day number, e.g. "04" or "23".

<month>
One of "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" (case-sensitive).

<year>
4 digit year number, e.g. "1990" or "2016".

<hour>
2 digit hour number, e.g. "09" or "23".

<minute>
2 digit minute number, e.g. "04" or "59".

<second>
2 digit second number, e.g. "04" or "59".

GMT
Greenwich Mean Time. HTTP dates are always expressed in GMT, never in local time.

EXAMPLES:
If-Range: Wed, 21 Oct 2015 07:28:00 GMT

*/