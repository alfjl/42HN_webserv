/*

Makes request conditional.

Server will only return requested resources for GET & HEAD methods, 
or upload resource for PUT & other non-safe methods, if resource matches one of listed ETag values.
If conditional does not match 412 (Precondition Failed) -> response is returned.

Comparison with stored ETag uses strong comparison algorithm, meaning 2 files are considered identical byte by byte only.
If listed ETag has W/ prefix indicating a weak entity tag, comparison algorithm will never match it.

2 common use cases:

GET & HEAD methods, used in combination with Range header, 
can guarantee that new ranges requested come from same resource as previous one.
Other methods, & in particular for PUT, If-Match is used to prevent the lost update problem. 
Checks if modification of resource that user wants to upload will not override another change 
that has been done since the original resource was fetched.

SYNTAX:
If-Match: <etag_value>
If-Match: <etag_value>, <etag_value>, …

DIRECTIVES:
<etag_value>
Entity tags uniquely represent requested resources. String of ASCII characters in double quotes (like "675af34563dc-tr34"). 
Prefixed by W/ indicates that they are "weak", i.e. they represent resource semantically but not byte-by-byte. 
In If-Match header, weak entity tags never match.

*
Asterisk is special value representing any resource. 
This must match as false, if origin server does not have current representation for target resource.

EXAMPLES:
If-Match: "bfc13a64729c4290ef5b2c2730249c88ca92d82d"

If-Match: "67ab43", "54ed21", "7892dd"

If-Match: *

*/