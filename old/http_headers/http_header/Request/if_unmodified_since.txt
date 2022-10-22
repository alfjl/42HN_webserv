/* 

makes request for resource conditional: 
Server sends requested resource or accepts it if POST or another non-safe method only 
if resource wasn't modified after date specified by thia HTTP header. 
If resource wasn't modified after specified date, responds with 412 Precondition Failed error.

If-Unmodified-Since HTTP header commonly used in following situations: 
In conjunction with non-safe methods, like POST, used to implement optimistic concurrency control, like some wikis: 
editions are rejected if stored document was modified since original was retrieved.
In conjunction with range request using the Range header, used to ensure that new fragment requested comes from unmodified document.

SYNTAX:
If-Unmodified-Since: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT

DIRECTIVES:
<day-name>
3-letter description of day of week. One of "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", or "Sun" (case-sensitive).

<day>
2-digit day number of month. Examples: "04", "23".

<month>
3-letter description of month. 
One of "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" (case-sensitive).

<year>
4-digit year number. Examples: "1990", "2016".

<hour>
2-digit hour number based on 24-hour system. Examples: "09", "23".

<minute>
2-digit minute number. Examples: "04", "59".

<second>
2-digit second number. Examples: "04", "59".

GMT
Greenwich Mean Time. HTTP dates are always expressed in GMT, never in local time.

EXAMPLES:
If-Unmodified-Since: Wed, 21 Oct 2015 07:28:00 GMT

*/