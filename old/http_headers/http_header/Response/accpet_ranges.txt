/* 
HTTP response header 

Marker used by server to advertise support for partial requests from client for file downloads.
Value indicates the usable unit to define a range.

Presence of Accept-Ranges header 
-> browser may try to resume interrupted download instead of trying to restart the dowload.

SYNTAX:
Accept-Ranges: <range-unit>
Accept-Ranges: none

DIRECTIVES
<range-unit>
Defines the range unit that the server supports.
Though bytes is the only range unit formally defined by RFC 7233, 
additional range units may be registered in theHTTP Range Unit Registry.

none
Indicates that no range unit is supported.
This makes the header equivalent of its own absence and is therefore, rarely used.
Although in some browsers, like IE9, 
this setting is used to disable or remove the pause buttons in the download manager.

EXAMPLES
Accept-Ranges: bytes

*/