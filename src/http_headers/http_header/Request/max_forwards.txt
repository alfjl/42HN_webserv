/* 

Used with TRACE method to limit number of nodes (usually proxies) that request goes through.
Value is integer indicating maximum amount of nodes it must visit.
Each node, decrements value & TRACE request is forwarded to next node,
until destination is reached, or received value of Max-Forwards is zero.
Request is then sent back, except for some headers, as the body of a 200 OK response.

If not present in TRACE request, node assumes there is no maximum number of forwards.

SYNTAX:
Max-Forwards: <integer>

EXAMPLES:
Max-Forwards: 0
Max-Forwards: 10
*/