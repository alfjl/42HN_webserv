# 42HN_webserv
Just a friendly little WebServer

The goal of the **webserv** project is to write a HTTP server in C++ 98.

## Description

The program has to take a configuration file as an argument, or use a [default config](https://github.com/alfjl/42HN_webserv/blob/main/web/basic.conf). It must be non-blocking and use only one select()/poll()/kqueue() call. Select() (or equivalent) has to check read() and write() at the same time. Checking the value of errno is forbidden. The server should be able to listen to multiple ports.  
It has to be compatible with at least one web browser of your choice and serve a fully static website. Fork() is only allowed to be used for CGIs. The use of threads is forbidden. Clients should be able to upload files. At least implement GET, POST and DELETE methods.

## Learnings

I learned a lot about the inner workings of web browsers, like the HTTP protocoll and working with sockets. Since we were not allowed to use threads, I learned more about I/O Multiplexing.

## Testing

The project included a couple of automatic functionality tests, which had to be passed, plus a stress test, to check, if the server was really non-blocking and didn't hang.

## Resources

* [network programming basics in C](https://beej.us/guide/bgnet/html)
* [network programming (German)](https://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap11-000.htm#RxxKap11000040003691F041100)
* [HTTP/1.1 RFC](https://www.rfc-editor.org/rfc/rfc2616)
* [CGI RFC](https://www.rfc-editor.org/rfc/rfc3875)
* [LL1 Parsing](https://en.wikipedia.org/wiki/LL_parser)
