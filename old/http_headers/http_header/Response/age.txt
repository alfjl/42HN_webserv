/*

Contains time in seconds the object was in a proxy cache.

Usually close to zero. If Age is: 0, was probably fetched from origin server; otherwise, 
usually calculated as difference between proxy's current date & Date general header included in HTTP response.

SYNTAX:
Age: <delta-seconds>

DIRECTIVES:
<delta-seconds>
A non-negative integer that is time in seconds the object was in a proxy cache.

EXAMPLES:
Age: 24

*/