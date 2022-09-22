/* 

Used to indicate original media type of resource (before content is encoded for sending).

In responses, provides client with actual content type of returned content. 
It's value may be ignored, e.g. when browsers perform MIME sniffing; 
set the X-Content-Type-Options header value to nosniff to prevent this behavior.

In requests, (such as POST or PUT), client tells server what type of data is actually sent.

SYNTAX:
Content-Type: text/html; charset=UTF-8
Content-Type: multipart/form-data; boundary=something

DIRECTIVES:
media-type
The MIME type of the resource or the data.

charset
The character encoding standard.

boundary
Multipart entities require boundary directive. Directive consists of 1 to 70 characters from a set of characters 
(and not ending with white space) known to be very robust through email gateways. 
Used to encapsulate boundaries of multiple parts of message. 
Often, boundary is prepended with 2 dashes & final boundary has 2 dashes appended at the end.

EXAMPLES:
Content-Type in HTML forms
In POST request, resulting from HTML form submission, Content-Type request is specified by enctype attribute on <form> element.

<form action="/" method="post" enctype="multipart/form-data">
  <input type="text" name="description" value="some text">
  <input type="file" name="myFile">
  <button type="submit">Submit</button>
</form>

Request looks like this (less interesting headers are omitted here):

POST /foo HTTP/1.1
Content-Length: 68137
Content-Type: multipart/form-data; boundary=---------------------------974767299852498929531610575

-----------------------------974767299852498929531610575
Content-Disposition: form-data; name="description"

some text
-----------------------------974767299852498929531610575
Content-Disposition: form-data; name="myFile"; filename="foo.txt"
Content-Type: text/plain

(content of the uploaded file foo.txt)
-----------------------------974767299852498929531610575--
*/