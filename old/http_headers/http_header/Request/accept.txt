// request HTTP header

// indicates which content types, expresses as ‘MIME types’, the client understands.
// Server uses ‘content negotiation’ to select proposal & informs client of choice with ‘Content-Type’ response header.
// Browser set required values for header based on context of request.
// (e.g. browser uses different values in request when fetching a CSS stylesheet, image, video or script)

// SYNTAX:
// Accept: <MIME_type>/<MIME_subtype>
// Accept: <MIME_type>/*
// Accept: */*

// // Multiple types, weighted with the quality value syntax:
// Accept: text/html, application/xhtml+xml, application/xml;q=0.9, image/webp, */*;q=0.8

// DIRECTIVES
// <MIME_type>/<MIME_subtype>
// A single, precise MIME type, like text/html.

// <MIME_type>/*
// A MIME type, but without a subtype. image/* corresponds to image/png, image/svg, image/gif, and other image types.

// */*
// Any MIME type

// ;q= (q-factor weighting)
// A value used is placed in an order of preference expressed using a relative quality value called the weight.

// EXAMPLES
// Accept: text/html

// Accept: image/*

// // General default
// Accept: */*

// // Default for navigation requests
// Accept: text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8

