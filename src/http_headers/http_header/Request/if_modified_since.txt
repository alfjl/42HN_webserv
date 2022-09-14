/* 

Makes request conditional: Server sends back requested resource, with a 200 status, only if last modified after given date. 
If resource wasn't modified since, response is a 304 without any body; 
Last-Modified response of previous request contains date of last modification. Unlike If-Unmodified-Since,
If-Modified-Since only used with GET or HEAD.

in combination with If-None-Match, is ignored, unless server doesn't support If-None-Match.

Most common use case is to update a cached entity that has no associated ETag.

SYNTAX:
If-Modified-Since: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT

DIRECTIVES:
<day-name>
One of "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", or "Sun" (case-sensitive).

<day>
2 digit day number, e.g. "04" or "23".

<month>
One of "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" (case sensitive).

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
If-Modified-Since: Wed, 21 Oct 2015 07:28:00 GMT

*/