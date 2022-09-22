/* 

:authority:
:method:
:path:
:scheme:
accept ***
accept-encoding ***
accept-language ***
chache-control ***
cookie ***

HTTP Request (Anfrage des Clients)

Accept:	
Welche Inhaltstypen der Client verarbeiten kann; ist das Feld leer, sind das alle Inhaltstypen.	
-> Accept: text/html, application/xml

Accept-Charset:
Welche Zeichensätze der Client anzeigen kann.	
-> Accept-Charset: utf-8

Accept-Encoding:	
Welche komprimierten Formate der Client unterstützt.	
-> Accept-Encoding: gzip

Accept-Language:
Gewünschte Sprachversion	
-> Accept-Language: de-DE

Authorization:
Authentifizierungsdaten (z. B. für einen Login)	
-> Basic WjbU7D25zTAlV2tZ7==

Cache-Control:	
Optionen des Caching-Mechanismus	
-> Cache-Control: no-cache

Cookie:
Cookie, das für diesen Server gespeichert wurde	
-> Cookie: $Version=1; Content=23

Content-Length:
Länge des Request-Bodys	
-> Content-Length: 212

Content-Type:
MIME-Typ des Bodys; relevant bei POST- und PUT-Requests	
-> Content-Type: application/x_222-form-urlencoded

Date:
Datum und Zeit des Requests	
-> Date: Mon, 9 March 2020 09:02:22 GMT

Expect:	
Formuliert eine Erwartung an den Server, in der Regel das Empfangen eines umfangreichen Requests.
-> Expect: 100-continue (der Server soll Code 100 senden, wenn er bereit ist, den Request zu empfangen)

Host:
Domain-Name des Servers
-> Host: ionos.de

If-Match:	
Bedingtes Ausführen einer Aktion, abhängig vom Übereinstimmen eines gesendeten Codes
-> If-Match: „ft678iujhnjio90’pöl“

If-Modified-Since:
Nur senden, wenn der angefragte Inhalt seit dem angegebenen Zeitpunkt verändert wurde
-> IF-Modified-Since: Mon 2 Mar 2020 1:00:00 GMT

If-None-Match:
Wie oben, aber über einen ETag (Entity-Tag, s. u.) spezifiziert
-> If-None-Match: „cxdrt5678iujhgbvb“

If-Range:
Fordert nur den Teil des Contents an, der geändert wurde bzw. im Client-Cache fehlt
-> If-Range: Mon 2 Mar 2020 1:00:00 GMT

If-Unmodified-Since:
Analog IF-Modified-Since
-> If-Modified-Since: Mon 2 Mar 2020 1:00:00 GMT

Max-Forwards:
Definiert, wie oft die Antwort des Servers maximal weitergeleitet werden darf	
-> Max-Forwards: 12

Proxy-Authorization:
Wird verwendet, um den Client bei einem Proxy-Server zu authentifizieren	
-> Proxy-Authorization: Basic WjbU7D25zTAlV2tZ7==

Range:
Spezifiziert einen Teilbereich des angeforderten Inhalts	
-> Range: bytes=0-9999

Referrer:
URL der Ressource, von der aus der Request kommt (d. h. von der aus verlinkt wurde)	
-> Referrer: https://example.com/index.html

TE:
Akzeptierte Extension-Transfer-Codierung	
-> TE: gzip, deflate

User-Agent:
User-Agent des Clients (vereinfacht gesagt: der Browser)	
-> Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.132 Safari/537.36
*/
