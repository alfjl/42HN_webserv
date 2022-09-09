/* 
Deletes specified resource 

Rules:
Request has body -> MAY
Successful response has body -> MAY
Safe -> NO
Idempotent -> YES
Cacheable -> NO
Allowed in HTML forms -> NO

Syntax: 
DELETE /file.html HTTP/1.1

Response:
If successful
1. 202 Accepted -> if action will likely succeed but has not yet been enacted
2. 204 No Content -> if action has been enacted & no further information is supplied
3. 200 OK -> if action had been enacted & response message includes a representation describing the status
*/