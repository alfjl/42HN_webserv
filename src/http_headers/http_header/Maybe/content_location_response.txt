/* 

Indicates alternate location for returned data. 
Principal use to indicate URL of a resource transmitted as result of content negotiation.

Location & Content-Location are different. Location indicates URL of a redirect, 
while Content-Location indicates direct URL to use to access the resource, without further content negotiation in the future. 
Location is header associated with response, while Content-Location is associated with data returned. 
This distinction may seem abstract without examples.

SYNTAX:
Content-Location: <url>

DIRECTIVES:
<url>
A relative (to the request URL) or absolute URL.

EXAMPLES:
Requesting data from server in different formats
Site's API returns data in JSON, XML, or CSV formats. If URL for a particular document is at https://example.com/documents/foo, 
the site could return different URLs for Content-Location depending on request's Accept header:

Request header							Response header
Accept: application/json, text/json		Content-Location: /documents/foo.json
Accept: application/xml, text/xml		Content-Location: /documents/foo.xml
Accept: text/plain, text/*				Content-Location: /documents/foo.txt
Example URLs — site could serve different filetypes with any URL patterns it wishes, 
such as a query string parameter: /documents/foo?format=json, /documents/foo?format=xml, and so on.

Client remembers that JSON version is available at that particular URL, skipping content negotiation the next time it requests that document.

Server could consider other content negotiation headers, such as Accept-Language.

Pointing to new document (HTTP 201 Created)
Say you're creating a new blog post through a site's API:

POST /new/post
Host: example.com
Content-Type: text/markdown
# My first blog post!
I made this through `example.com`'s API. I hope it worked.

Site returns published post in response body. Server specifies where new post is with Content-Location header,
indicating that this location refers to content (the body) of this response:

HTTP/1.1 201 Created
Content-Type: text/markdown
Content-Location: /my-first-blog-post
# My first blog post
I made this through `example.com`'s API. I hope it worked.

Indicating the URL of a transaction's result
Say you have a <form> for sending money to another user of a site.

<form action="/send-payment" method="post">
  <p>
    <label>Who do you want to send the money to?
      <input type="text" name="recipient">
    </label>
  </p>
  <p>
    <label>How much?
      <input type="number" name="amount">
    </label>
  </p>
  <button type="submit">Send Money</button>
</form>

When form is submitted, site generates a receipt for transaction. 
Server could use Content-Location to indicate that receipt's URL for future access.

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Location: /my-receipts/38
<!doctype html>
(Lots of HTML…)
<p>You sent $38.00 to ExampleUser.</p>
(Lots more HTML…)

*/