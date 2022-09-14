/* 

Lists set of methods supported by a resource.

Must be sent if server responds with 405 Method Not Allowed to indicate which request methods can be used.
If empty, indicates that resource allows no request methods, which might occur temporarily e.g. for given resource.

SYNTAX:
Allow: <http-methods>

DIRECTIVES:
<http-methods>
Comma-separated list of allowed HTTP request methods.

EXAMPLES:
Allow: GET, POST, HEAD

*/