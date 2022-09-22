/* 

Allows web site administrators to control resources the user agent is allowed to load for a given page. 
With a few exceptions, policies mostly involve specifying server origins & script endpoints. 
This helps guard against cross-site scripting attacks (Cross-site_scripting).

For more information, see the introductory article on Content Security Policy (CSP).

SYNTAX:
Content-Security-Policy: <policy-directive>; <policy-directive>
where <policy-directive> consists of: <directive> <value> with no internal punctuation.

DIRECTIVES:
Fetch

Document

Navigation

Reporting

Other

Deprecated

VALUES:

Keyword

Unsafe Keyword

Host

Other

CSP IN WORKERS

MULTIPLE CONTENT SECURITY POLICIES


*/