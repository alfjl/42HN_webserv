/*
contains an Internet email address for a human user who controls the requesting user agent.

If running a robotic user agent (e.g. a crawler), this header must be sent, 
so you get contacted if problems occur on servers, e.g. if robot sends excessive, unwanted, or invalid requests.

Warning: Do NOT use From header for access control or authentication.

SYNTAX:
From: <email>

DIRECTIVES:
<email>
A machine-usable email address.

EXAMPLES:
From: webmaster@example.org
*/