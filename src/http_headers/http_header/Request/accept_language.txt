/* 
request HTTP header

indicates natural language & locale the client prefers.
Server uses ‘content negotiation’ to select proposal & informs client of choice with ‘Content-Language’ response header.
Browser set required values for this header according to their active user interface language.
Changes are not recommended due to fingerprinting.

Serves as hint when server cannot determine target content language (e.g. use specific URL that depends on explicit user decision).
Server should never override explicit language choice.
Content of ‘Accepted-Language’ is often out of user’s control (e.g. when traveling).
Users may want to visit pages in languages different from user interface language.

Server possible can send back ‘406 Not Acceptable’ when unable to serve content in matching language.
Rarely implemented for better user experience -> servers often ignore ‘Accept-Language’ in this case

SYNTAX:
Accept-Language: <language>
Accept-Language: *

// Multiple types, weighted with the quality value syntax:
Accept-Language: fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5

DIRECTIVES:
<language>
A language tag (which is sometimes referred to as a "locale identifier"). 
This consists of a 2-3 letter base language tag that indicates a language, optionally followed by additional subtags separated by '-'. 
The most common extra information is the country or region variant (like 'en-US' or 'fr-CA') or the type of alphabet to use (like 'sr-Latn'). 
Other variants, like the type of orthography ('de-DE-1996'), are usually not used in the context of this header.

*
Any language; '*' is used as a wildcard.

;q= (q-factor weighting)
Any value placed in an order of preference expressed using a relative quality value called weight.

EXAMPLES:
Accept-Language: de

Accept-Language: de-CH

Accept-Language: en-US,en;q=0.5
*/