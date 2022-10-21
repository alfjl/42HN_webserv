/*

indicates the URL to redirect a page to. Only provides meaning when served with 3xx (redirection) or 201 (created) status response.

If redirected, HTTP method used to make new request to fetch page pointed to by Location depends on original method & kind of redirection:

303 (See Other) responses always lead to the use of a GET method.
307 (Temporary Redirect) & 308 (Permanent Redirect) don't change the method used in the original request.
301 (Moved Permanently) & 302 (Found) don't change the method most of the time, though older user-agents may (so you basically don't know).
All responses with one of these status codes send a Location header.

In cases of resource creation, it indicates the URL to the newly created resource.

Location & Content-Location are different. Location indicates the target of a redirection or the URL of a newly created resource.
Content-Location indicates direct URL to use to access resource when content negotiation happened, without need of further content negotiation.
Location is a header associated with the response, while Content-Location is associated with the entity returned.

SYNTAX:
Location: <url>

DIRECTIVES:
<url>
A relative (to the request URL) or absolute URL.

EXAMPLES:
Location: /index.html

*/