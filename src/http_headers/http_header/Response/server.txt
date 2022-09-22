/*

describes software used by origin server that handled request — server that generated the response.

Warning: Avoid overly-detailed Server values, they can reveal information that may make it easier for attackers to exploit known security holes.

SYNTAX:
Server: <product>

DIRECTIVES:
<product>
A name of the software or the product that handled the request. Usually in a format similar to User-Agent.

How much detail to include is an interesting balance to strike; exposing the OS version is probably a bad idea, 
as mentioned in the earlier warning about overly-detailed values. However, 
exposed Apache versions helped browsers to work around a bug of the versions with Content-Encoding and Range in combination.

EXAMPLES:
Server: Apache/2.4.1 (Unix)

*/