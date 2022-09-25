/*
which response class do we have?
If there is a problem with the request then we get a 4XX response
If there is a problem with the server side we get a 5XX response
For the rest there are 2XX/3XX responses (1XX responses are irrelevant)

how do we know that there is a problem with the request or the server side?
Does that mean that the 2XX/3XX responses mean there are no problems?

2XX/3XX Tree
If you want to redirect the user to a new location & the new location is temporary (302 Found)
Else (301 Moved Permanently)

If you don't want to redirect the user to a new location (200 OK)

4XX Tree Problem with Request
If the resource does not exists (404 Not Found)
Else (400 Bad Request)

Optional but useful:
If the user is being throttled (429 Too Many Requests) if we are twitter (420 Enhance Your Calm)
Irrelevant but funny:
If it is the 1st of April (418 I'm a Teapot)

5XX Tree Problem with the Server
If we don't feel bad that our code can't handle the request (500 Internal Server Error)

Optional but useful:
If the server should retry after some time (503 Service Unaavilable)

*/

/*

if (request problem){
	if (resource doesn't exist)
		return 404;
	else
		return 400;

	optional:
	if (user is being throttled)
		return 429; (or 420)
}
else if (server-side problem){
	if (cannot handle request)
		return 500;

	optional:
	if (server retry again)
		return 503;
}
else {
	if (redirecting user to new location & new location temporary)
		return 302;
	else if (redirecting user to new location & new location not temporary)
		return 301;
	else if (redirecting user not to new location)
		return 200;
}

*/