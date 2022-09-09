/* 

Etag (entity tage) Identifier for specific version of a resource. 
Makes caches more efficient & save bandwidth, as web server does not need to resend full response if content was not changed. 
Additionally, helps to prevent simultaneous updates of resource from overwriting each other ("mid-air collisions").

If resource at given URL changes, new Etag value must be generated. 
Comparison of them can determine whether 2 representations of a resource are the same. 
Etags are similar to fingerprints, & might also be used for tracking purposes by some servers. 
Might also be set to persist indefinitely by a tracking server.

SYNTAX:
ETag: W/"<etag_value>"
ETag: "<etag_value>"

DIRECTIVES:
W/ Optional
'W/' (case-sensitive) indicates that a weak validator is used. 
Weak etags are easy to generate, but are far less useful for comparisons. 
Strong validators are ideal for comparisons but can be very difficult to generate efficiently. 
Weak ETag values of two representations of the same resources might be semantically equivalent, but not byte-for-byte identical. 
This means weak etags prevent caching when byte range requests are used, but strong etags mean range requests can still be cached.

"<etag_value>"
Entity tag that uniquely represents the requested resource. 
It is a string of ASCII characters placed between double quotes, like "675af34563dc-tr34". 
The method by which ETag values are generated is not specified. 
Typically, the ETag value is a hash of the content, a hash of the last modification timestamp, or just a revision number. 
For example, a wiki engine can use a hexadecimal hash of the documentation article content.

EXAMPLES:
ETag: "33a64df551425fcc55e4d42a148795d9f25f89d4"
ETag: W/"0815"

*/