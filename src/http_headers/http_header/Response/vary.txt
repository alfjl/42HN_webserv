/*

Describes parts of request message aside from method & URL that influenced content of response it occurs in. 
Most often, this is used to create a cache key when content negotiation is in use.

Same Vary header value should be used on all responses for a given URL, including 304 Not Modified responses & "default" response.

SYNTAX:
Vary: *
Vary: <header-name>, <header-name>, ...

DIRECTIVES:
*
Indicates that factors other than request headers influenced the generation of this response. Implies that the response is uncacheable.

<header-name>
Comma-separated list of request header names that could have influenced the generation of this response.


*/