/* 

lists any encodings that have been applied to the representation (message payload), and in what order. 
This lets the recipient know how to decode the representation in order to obtain the original payload format. 
Content encoding is mainly used to compress the message data without losing information about the origin media type.

Original media/content type is specified in Content-Type header, & Content-Encoding applies to representation, or "coded form", of data. 
If original media is encoded (e.g. a zip file) then information would not be included in Content-Encoding header.

Servers should compress data as much as possible, & should use content encoding where appropriate. 
Compressing a compressed media type like zip/jpeg may not be appropriate, as it can make the payload larger.

SYNTAX:
Content-Encoding: gzip
Content-Encoding: compress
Content-Encoding: deflate
Content-Encoding: br

// Multiple, in the order in which they were applied
Content-Encoding: deflate, gzip

DIRECTIVES:
gzip
Format using Lempel-Ziv coding (LZ77), with 32-bit CRC. Original format of UNIX gzip program.
HTTP/1.1 standard recommends that servers supporting this content-encoding should recognize x-gzip as an alias, for compatibility purposes.

compress
Format using Lempel-Ziv-Welch (LZW) algorithm. Value name taken from UNIX compress program, which implemented this algorithm. 
Like the compress program, which has disappeared from most UNIX distributions, 
this content-encoding is not used by many browsers today, partly because of a patent issue (expired in 2003).

deflate
Using zlib structure (defined in RFC 1950) with deflate compression algorithm (defined in RFC 1951).

br Non-standard
A format using the Brotli algorithm.

EXAMPLES:
Compressing with gzip
Client side, one can advertise a list of compression schemes that are sent by HTTP request. 
Accept-Encoding header is used for negotiating content encoding.

Accept-Encoding: gzip, deflate
Server responds with scheme used, indicated by Content-Encoding response header.

Content-Encoding: gzip
Server is not obligated to use any compression method. Compression highly depends on server settings & used server modules.

*/