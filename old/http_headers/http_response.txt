/* 
access-control-allow-origin
chache-control
cf-chache-status
cf-ray
content-encoding *** 
content-language 
content-type ***
date ***
net
protocol *
server ***
set-cookie **
strict-transport-security
vary

HTTP-Response (Antwort des Servers)

Accept-Ranges:
Welche Einheiten der Server für die Range-Angaben (s. o.) akzeptiert
-> Accept-Ranges: bytes

Age:
Anzahl der Sekunden, in denen das Objekt im Cache gelegen hat
-> Age: 2300

Allow:
Erlaubte Request-Typen für eine bestimmte Ressource
-> Allow: GET, POST, HEAD

Cache-Control:
Ob und wie lange das Objekt im Cache gehalten werden darf
-> Cache-Control: max-age=4800

Connection:
Bevorzugte Art der Verbindung
-> Connection: close

Content-Encoding:
Art der Komprimierung
-> Content-Encoding: deflate

Content-Language:
Sprache der Ressource
-> Content-Language: de-DE

Content-Length:
Größe des Bodys in Bytes
-> Content-Length: 135674

Content-Location:
Speicherort der Datei, falls sie von einem anderen Speicherort kommt als angefragt (z. B. bei CDN)
-> Content-Location: /example.de

Content-Security-Policy:
Sicherheitskonzepte des Servers
-> Content-Security-Policy: frame-src 'none‘; object-src 'none‘

Content-Type:
MIME-Typ der angeforderten Datei
-> Content-Type: text/tml; charset=utf-8

Date:
Zeitpunkt der Response
-> Date: Mon 2 Mar 2020 1:00:00 GMT

ETag:
Markiert eine bestimmte Version der Datei
-> ETag: „vt6789oi8uztgfvbn“

Expires:
Ab wann die Datei als veraltet betrachtet werden sollte
-> Expires: Tue 3 Mar 2020 1:00:00 GMT

Last-Modified:
Zeitpunkt der letzten Änderung der Datei
-> Last-Modified: Mon 2 Mar 2020 1:00:00 GMT

Location:
Kennzeichnet den Speicherort, an den die Anfrage weitergeleitet wurde
-> Location: https://www.example.com

Proxy-Authenticate:
Sagt, ob und wie der Client sich beim Proxy authentifizieren muss
-> Proxy-Authenticate: Basic

Retry-After:
Ab wann der Client nochmals anfragen soll, falls die Ressource temporär nicht verfügbar ist (Datum oder Sekunden)
-> Retry-After: 300

Server:
Kennung des Servers
-> Server: Apache

Set-Cookie:
Setzt ein Cookie beim Client
-> Set-Cookie: UserID=XY; Max-Age=3800; Version=1

Transfer-Encoding:
Kompressionsmethode
-> Transfer-Encoding: gpzip

Vary:
Sagt, welche Header-Felder als variierend betrachtet werden sollen, falls eine Datei aus dem Cache angefordert wird.
-> Vary: User-Agent (= der Server hält verschiedene Dateiversionen je nach User Agent bereit)

Via:
Über welche Proxys die Antwort gesendet wurde.
-> Via: 1.1www.ionos.de
*/