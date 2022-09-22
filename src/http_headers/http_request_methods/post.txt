/* 
Sends data to the server. Body type of the request is indicated by Content-Type header.

POST is successive identical and has additional effects to PUT like passing an order several times

POST requests are send via HTML form which results in a change on the server. The content type gets selected by putting the adequate string type in the enctype attribute of the <form> element or the formenctype attribute of the <input> or <button> element
1. Application/x-www-form-urlcoded: the keys & values are encoded in key-value tuples separated by ‘&’ with a ‘=’ between key & value.
Non-alphanumeric characters in keys & values are precent encoded: therefore this type is not suitable to use with binary data (use ‘multipart/form-data’ instead)
2. multipart/form-data: every value is send as one block of data (“body part”) with a user agent-defined delimiter (“boundary”) separating each part. Keys are given in ‘Content-Disposition’ header of each part.
3. text/plain

When POST request is sent via other method than HTML form (e.g. XMLHttpRequest) body can be any type. POST is designed to allow a uniform method to cover these functions:
1. Annotation of existing resources
2. Posting messages to bulletin board, newsgroup, mailing list, or similar group of articles
3. Adding new user through signup modal
4. Providing block of data (e.g result of submitting form) to data-handling process
5. Extending database through append operation

Rules:
Request has body -> YES
Successful response has body -> YES
Safe -> NO
Idempotent -> NO
Cacheable -> Only if freshness information included
Allowed in HTML forms -> YES

Syntax: 
POST /test

Example:
1.
POST /test HTTP/1.1
Host: foo.example
Content-Type: application/x-ww-form-urlencoded
Content-Length: 27
field1=value1&field2=value2

2.
POST /test HTTP/1.1
Host: foo.example
Content-Type: application/x-ww-form-urlencoded
—boundary
Content-Disposition: form-data; name=“field1”
value1
—boundary
Content-Disposition: form-data; name=“field2”; filename=“example.txt”
value2
—boundary—

*/