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

RESPONSE DIRECTIVES:
// max-age
// The max-age=N response directive indicates that the response remains fresh until N seconds after the response is generated.
// Cache-Control: max-age=604800
// Indicates that caches can store this response and reuse it for subsequent requests while it's fresh.

// Note that max-age is not the elapsed time since the response was received; 
// it is the elapsed time since the response was generated on the origin server. 
// So if the other cache(s) — on the network route taken by the response — store the response for 100 seconds 
// (indicated using the Age response header field), the browser cache would deduct 100 seconds from its freshness lifetime.
// Cache-Control: max-age=604800
// Age: 100
// s-maxage
// The s-maxage response directive also indicates how long the response is fresh for (similar to max-age) 
// — but it is specific to shared caches, and they will ignore max-age when it is present.
// Cache-Control: s-maxage=604800
// no-cache
// The no-cache response directive indicates that the response can be stored in caches, 
// but the response must be validated with the origin server before each reuse, 
// even when the cache is disconnected from the origin server.
// Cache-Control: no-cache
// If you want caches to always check for content updates while reusing stored content, no-cache is the directive to use.
//  It does this by requiring caches to revalidate each request with the origin server.

// Note that no-cache does not mean "don't cache". 
// no-cache allows caches to store a response but requires them to revalidate it before reuse. 
// If the sense of "don't cache" that you want is actually "don't store", then no-store is the directive to use.

// must-revalidate
// The must-revalidate response directive indicates that the response can be stored in caches and can be reused while fresh. 
// If the response becomes stale, it must be validated with the origin server before reuse.

// Typically, must-revalidate is used with max-age.
// Cache-Control: max-age=604800, must-revalidate
// HTTP allows caches to reuse stale responses when they are disconnected from the origin server. 
// must-revalidate is a way to prevent this from happening 
// - either the stored response is revalidated with the origin server or a 504 (Gateway Timeout) response is generated.

// proxy-revalidate
// The proxy-revalidate response directive is the equivalent of must-revalidate, but specifically for shared caches only.

// no-store
// The no-store response directive indicates that any caches of any kind (private or shared) should not store this response.
// Cache-Control: no-store
// private
// The private response directive indicates that the response can be stored only in a private cache (e.g. local caches in browsers).
// Cache-Control: private
// You should add the private directive for user-personalized content, 
// especially for responses received after login and for sessions managed via cookies.

// If you forget to add private to a response with personalized content, 
// then that response can be stored in a shared cache and end up being reused for multiple users,
// which can cause personal information to leak.

// public
// The public response directive indicates that the response can be stored in a shared cache.
// Responses for requests with Authorization header fields must not be stored in a shared cache; 
// however, the public directive will cause such responses to be stored in a shared cache.
// Cache-Control: public
// In general, when pages are under Basic Auth or Digest Auth, the browser sends requests with the Authorization header.
// This means that the response is access-controlled for restricted users (who have accounts), 
// and it's fundamentally not shared-cacheable, even if it has max-age.

// You can use the public directive to unlock that restriction.
// Cache-Control: public, max-age=604800
// Note that s-maxage or must-revalidate also unlock that restriction.

// If a request doesn't have an Authorization header, or you are already using s-maxage or must-revalidate in the response,
// then you don't need to use public.

// must-understand
// The must-understand response directive indicates that a cache should store the response only if 
// it understands the requirements for caching based on status code.

// must-understand should be coupled with no-store for fallback behavior.
// Cache-Control: must-understand, no-store
// If a cache doesn't support must-understand, it will be ignored. If no-store is also present, the response isn't stored.

// If a cache supports must-understand, it stores the response with an understanding of cache requirements based on its status code.

// no-transform
// Some intermediaries transform content for various reasons. For example, some convert images to reduce transfer size. 
// In some cases, this is undesirable for the content provider.

// no-transform indicates that any intermediary (regardless of whether it implements a cache) shouldn't transform the response contents.

// Note: Google's Web Light is one kind of such an intermediary. 
// It converts images to minimize data for a cache store or slow connection and supports no-transform as an opt-out option.

// immutable
// The immutable response directive indicates that the response will not be updated while it's fresh.
// Cache-Control: public, max-age=604800, immutable
// A modern best practice for static resources is to include version/hashes in their URLs, 
// while never modifying the resources — but instead, when necessary, 
// updating the resources with newer versions that have new version-numbers/hashes, 
// so that their URLs are different. That's called the cache-busting pattern.

// <script src=https://example.com/react.0.0.0.js></script>
// When a user reloads the browser, the browser will send conditional requests for validating to the origin server. 
// Not necessary to revalidate these static resources even when user reloads browser, because they're never modified. 
// immutable tells a cache that the response is immutable while it's fresh 
// & avoids those kinds of unnecessary conditional requests to the server.

// When you use a cache-busting pattern for resources and apply them to a long max-age, you can also add immutable to avoid revalidation.

// stale-while-revalidate
// The stale-while-revalidate response directive indicates that the cache could reuse a stale response while it revalidates it to a cache.
// Cache-Control: max-age=604800, stale-while-revalidate=86400
// In the example above, the response is fresh for 7 days (604800s). 
// After 7 days it becomes stale, but the cache is allowed to reuse it for any requests that are made in the following day (86400s),
//  provided that they revalidate the response in the background.

// Revalidation will make the cache be fresh again, so it appears to clients that it was always fresh during that period 
// — effectively hiding the latency penalty of revalidation from them.

// If no request happened during that period, the cache became stale and the next request will revalidate normally.

// stale-if-error
// The stale-if-error response directive indicates that the cache can reuse a stale response 
// when an origin server responds with an error (500, 502, 503, or 504).
// Cache-Control: max-age=604800, stale-if-error=86400
// In the example above, the response is fresh for 7 days (604800s). After 7 days it becomes stale, 
// but it can be used for an extra 1 day (86400s) if the server responds with an error.

// After a period of time, the stored response became stale normally. 
// This means that the client will receive an error response as-is if the origin server sends it.
*/