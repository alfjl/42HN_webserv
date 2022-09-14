/* 

holds directives (instructions) — in requests & responses —
that control caching in browsers & shared caches (e.g. Proxies, CDNs).

SYNTAX:
Caching directives follow validation rules below:

1. Case-insensitive. Lowercase recommended as some implementations don't recognize uppercase directives.
2. Separate Multiple directives by comma.
3. Some directives have an optional argument.

CACHE DIRECTIVES
Standard Cache-Control directives:

Request 		Response
max-age 		max-age
max-stale		-
min-fresh		-
	-			s-maxage
no-cache		no-cache
no-store		no-store
no-transform	no-transform
only-if-cached	-
	-			must-revalidate
	-			proxy-revalidate
	-			must-understand
	-			private
	-			public
	-			immutable
	-			stale-while-revalidate
stale-if-error	stale-if-error

Note: Check https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cache-Control#browser_compatibility 
for their support; user agents that don't recognize them should ignore them.

HTTP CACHE
Shared Cache or Private Cache

Shared cache
Cache that exists between the origin server and clients (e.g. Proxy, CDN). 
It stores a single response and reuses it with multiple users 
— so developers should avoid storing personalized contents to be cached in the shared cache.

Private cache
Cache that exists in the client. It is also called local cache or browser cache. 
It can store and reuse personalized content for a single user.

// REQUEST DIRECTIVES:
// no-cache
// The no-cache request directive asks caches to validate the response with the origin server before reuse.

// Cache-Control: no-cache
// Copy to Clipboard
// no-cache allows clients to request the most up-to-date response even if the cache has a fresh response.

// Browsers usually add no-cache to requests when users are force reloading a page.

// no-store
// The no-store request directive allows a client to request that caches refrain from storing the request and corresponding response — even if the origin server's response could be stored.

// Cache-Control: no-store
// Copy to Clipboard
// Note that the major browsers do not support requests with no-store.

// max-age
// The max-age=N request directive indicates that the client allows a stored response that is generated on the origin server within N seconds — where N may be any non-negative integer (including 0).

// Cache-Control: max-age=3600
// Copy to Clipboard
// In the case above, if the response with Cache-Control: max-age=604800 was generated more than 3 hours ago (calculated from max-age and the Age header), the cache couldn't reuse that response.

// Many browsers use this directive for reloading, as explained below.

// Cache-Control: max-age=0
// Copy to Clipboard
// max-age=0 is a workaround for no-cache, because many old (HTTP/1.0) cache implementations don't support no-cache. Recently browsers are still using max-age=0 in "reloading" — for backward compatibility — and alternatively using no-cache to cause a "force reloading".

// If the max-age value isn't non-negative (for example, -1) or isn't an integer (for example, 3599.99), then the caching behavior is undefined. However, the Calculating Freshness Lifetime section of the HTTP specification states:

// Caches are encouraged to consider responses that have invalid freshness information to be stale.

// In other words, for any max-age value that isn't an integer or isn't non-negative, the caching behavior that's encouraged is to treat the value as if it were 0.

// max-stale
// The max-stale=N request directive indicates that the client allows a stored response that is stale within N seconds.

// Cache-Control: max-stale=3600
// Copy to Clipboard
// In the case above, if the response with Cache-Control: max-age=604800 was generated more than 3 hours ago (calculated from max-age and the Age header), the cache couldn't reuse that response.

// Clients can use this header when the origin server is down or too slow and can accept cached responses from caches even if they are a bit old.

// Note that the major browsers do not support requests with max-stale.

// min-fresh
// The min-fresh=N request directive indicates that the client allows a stored response that is fresh for at least N seconds.

// Cache-Control: min-fresh=600
// Copy to Clipboard
// In the case above, if the response with Cache-Control: max-age=3600 was stored in caches 51 minutes ago, the cache couldn't reuse that response.

// Clients can use this header when the user requires the response to not only be fresh, but also requires that it won't be updated for a period of time.

// Note that the major browsers do not support requests with min-fresh.

// no-transform
// Same meaning that no-transform has for a response, but for a request instead.

// only-if-cached
// The client indicates that cache should obtain an already-cached response. If a cache has stored a response, it's reused.
*/