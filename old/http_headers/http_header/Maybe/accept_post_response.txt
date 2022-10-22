// Response HTTP header 
// advertises which media types are accepted by the server for HTTP post requests.

// Accept-Post response to any method allows POST on the requested resource 
// (any document/media format in header indicates that document format is allowed).

// e.g. Server receives POST request with unsupported media type 
// -> could reply with 415 Unsupported Media Type & 
// Accept-Post header referencing one or more supported media types.

// Syntax
// Accept: <MIME_type>/<MIME_subtype>
// Accept: <MIME_type>/*
// Accept: */*

// DIRECTIVES:
// None

// EXAMPLES:
// Accept-Post: application/example, text/example
// Accept-Post: image/webp
// Accept-Post: */*
