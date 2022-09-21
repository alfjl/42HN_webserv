/* 

Contains stored HTTP cookies associated with the server 
(i.e. previously sent by the server with the Set-Cookie header or set in JavaScript using Document.cookie).

Optional & may be omitted if, the browser's privacy settings block cookies.

SYNTAX:
Cookie: <cookie-list>
Cookie: name=value
Cookie: name=value; name2=value2; name3=value3

DIRECTIVES:
<cookie-list>
A list of name-value pairs in the form of <cookie-name>=<cookie-value>. Pairs in the list are separated by a semicolon and a space ('; ').

EXAMPLES:
Cookie: PHPSESSID=298zf09hf012fh2; csrftoken=u32t4o3tb3gg43; _gat=1
*/