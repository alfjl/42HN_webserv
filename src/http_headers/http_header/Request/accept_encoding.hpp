/* 
request HTTP header & forbidden header name

indicates the content encoding (compression algorithm) that client can understand.
Server uses ‘content negotiation’ to select proposal & informs client of choice with ‘Content-Encoding’ response header.

Even if client & server support the same compression algorithms.
Server may not compress body of response if ‘identity’ value is also acceptable.
2 common cases:
1.
Data to be sent is already compressed -> second compression won’t reduce transmitted data size.
=> True for pre-compressed image formats (e.g. JPEG)
2.
Server is overloaded -> cannot compress.
(e.g. server should not compress if more than 80% computational power is used)  

If ‘identity;q=0’ or ‘*q;=0’ directives don’t explicitly forbid the ‘identity’ value which means no encoding 
-> server must never return ‘406 Not Acceptable’ error.

SYNTAX:
Accept-Encoding: gzip
Accept-Encoding: compress
Accept-Encoding: deflate
Accept-Encoding: br
Accept-Encoding: identity
Accept-Encoding: *

// Multiple algorithms, weighted with the quality value syntax:
Accept-Encoding: deflate, gzip;q=1.0, *;q=0.5

DIRECTIVES:
gzip
A compression format that uses the Lempel-Ziv coding (LZ77) with a 32-bit CRC.

compress
A compression format that uses the Lempel-Ziv-Welch (LZW) algorithm.

deflate
A compression format that uses the zlib structure with the deflate compression algorithm.

br
A compression format that uses the Brotli algorithm.

identity
Indicates the identity function (that is, without modification or compression). 
This value is always considered as acceptable, even if omitted.

*
Matches any content encoding not already listed in the header. 
This is the default value if the header is not present. 
This directive does not suggest that any algorithm is supported but indicates that no preference is expressed.

;q= (qvalues weighting)
Any value is placed in an order of preference expressed using a relative quality value called weight.

EXAMPLES:
Accept-Encoding: gzip

Accept-Encoding: gzip, compress, br

Accept-Encoding: br;q=1.0, gzip;q=0.8, *;q=0.1

*/