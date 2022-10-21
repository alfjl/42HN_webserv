/*

Makes request conditional. 
For GET & HEAD methods, server returns requested resource, with 200 status, only if no ETag matches the given ones. 
For other methods, request processes only if eventually existing resource's ETag doesn't match any listed values.

If condition fails for GET & HEAD, server must return HTTP code 304 (Not Modified).
For methods that apply server-side changes, use code 412 (Precondition Failed).
Server generating 304 response MUST generate any following header fields 
that would sent 200 (OK) response to same request: Cache-Control, Content-Location, Date, ETag, Expires, & Vary.

Comparison with stored ETag uses weak comparison algorithm -> 2 files are considered identical if content is equivalent 
=> no need to be identical byte by byte. e.g. 2 pages differ by creation date in footer are considered identical.

If combined with If-Modified-Since, If-None-Match has precedence (if server supports it).

2 common use cases:

GET & HEAD methods, update cached entity that has an associated ETag.
Other methods, & particular PUT, If-None-Match used with * value can be used to save file not known to exist,
guaranteeing no other upload happen before, losing data of previous put; Variation of lost update problem.

SYNTAX:
If-None-Match: "<etag_value>"
If-None-Match: "<etag_value>", "<etag_value>", …
If-None-Match: *

DIRECTIVES:
<etag_value>
Entity tags uniquely representing requested resources. String of ASCII characters in double quotes (Like "675af34563dc-tr34") 
& prefixed by W/ indicates weak comparison algorithm should be used (useless with If-None-Match as it only uses that algorithm).

*
Special value representing any resource. Only useful when uploading a resource, usually with PUT, 
to check if another resource with the identity has already been uploaded before.

Examples
If-None-Match: "bfc13a64729c4290ef5b2c2730249c88ca92d82d"

If-None-Match: W/"67ab43", "54ed21", "7892dd"

If-None-Match: *

 */