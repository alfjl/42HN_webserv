/* 

Specifies transfer encodings, user agent is accepting.
(informally call it Accept-Transfer-Encoding, it's more intuitive).

See also Transfer-Encoding response header for more details on transfer encodings. 
Chunked is always acceptable for HTTP/1.1 recipients & no need to specify "chunked" using TE header. 
Useful for setting if client is accepting trailer fields in a chunked transfer coding using the "trailers" value.

SYNTAX:
TE: compress
TE: deflate
TE: gzip
TE: trailers

// Multiple directives, weighted with the quality value syntax:
TE: trailers, deflate;q=0.5

DIRECTIVES:
compress
Format using Lempel-Ziv-Welch (LZW) algorithm is accepted as a transfer coding name.

deflate
Using zlib structure is accepted as transfer coding name.

gzip
Format using Lempel-Ziv coding (LZ77), with 32-bit CRC is accepted as transfer coding name.

trailers
Indicates that client is willing to accept trailer fields in chunked transfer coding.

q
When multiple transfer codings are acceptable, q parameter of quality value syntax can rank codings by preference.

*/