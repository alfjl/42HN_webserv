/* 
Indicates part of a document that server should return. 
Several parts can be requested with one Range header at once,
& server may send back these ranges in multipart document. 
If server sends back ranges, it uses 206 Partial Content for response.
If ranges are invalid, server returns 416 Range Not Satisfiable error.
Server can also ignore Range header & return whole document with 200 status code.

SYNTAX:
Range: <unit>=<range-start>-
Range: <unit>=<range-start>-<range-end>
Range: <unit>=<range-start>-<range-end>, <range-start>-<range-end>
Range: <unit>=<range-start>-<range-end>, <range-start>-<range-end>, <range-start>-<range-end>
Range: <unit>=-<suffix-length>

DIRECTIVES:
<unit>
Unit in which ranges are specified. Usually bytes.

<range-start>
Integer in given unit indicating beginning of request range.

<range-end>
Integer in given unit indicating end of requested range. 
Value is optional &, if omitted, end of document is taken as end of range.

<suffix-length>
Integer in given unit indicating number of units at end of file to return.

EXAMPLES:
Requesting three ranges from file.
Range: bytes=200-1000, 2000-6576, 19000-

Requesting first 500 & last 500 bytes of file. Request may be rejected by server if ranges overlap.
Range: bytes=0-499, -500

*/