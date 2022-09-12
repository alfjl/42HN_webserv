/*

Used to describe language(s) intended for audience, so users can differentiate it according to their own preferred language.

E.g. if "Content-Language: de-DE" is set, the document is intended for German language speakers 
(however, it doesn't indicate the document is written in German. 
E.g. might be written in English as part of a language course for German speakers. 
To indicate which language the document is written in, use the lang attribute instead).

If no Content-Language is specified, default is, content is intended for all language audiences. 
Multiple language tags are also possible, as applying Content-Language header to various media types & not only to textual documents.

SYNTAX:
Content-Language: de-DE
Content-Language: en-US
Content-Language: de-DE, en-CA

DIRECTIVES:
language-tag
Multiple language tags are comma-separated. 
Each language tag is a sequence of one or more case-insensitive subtags, each separated by a hyphen character ("-", %x2D).
Language tags consists of primary language subtag identifying a broad family of related languages (e.g., "en" = English) 
& is optionally followed by a series of subtags that refine or narrow the language's range (e.g., "en-CA" = Canadian-English).

EXAMPLES:
Indicating document language
Global lang attribute is used on HTML elements to indicate the language of an entire HTML document or parts of it.
<html lang="de">

// Do not use this meta element like this for stating a document language:
// <!-- /!\ This is bad practice -->
// <meta http-equiv="content-language" content="de">

Indicating a target audience for a resource
Used to specify page's intended audience & indicates if this is more than one language.
Content-Language: de, en
*/