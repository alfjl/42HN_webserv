/*

Contains date & time when origin server believes resource was last modified. 
Used as validator to determine if resource is same as previously stored one. 
Less accurate than an ETag header, it is a fallback mechanism. 
Conditional requests containing If-Modified-Since or If-Unmodified-Since headers make use of this field.

SYNTAX:
Last-Modified: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT

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
Last-Modified: Wed, 21 Oct 2015 07:28:00 GMT


*/