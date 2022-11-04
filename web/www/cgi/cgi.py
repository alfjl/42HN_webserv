import sys

print("Status: 200 OK", end="\r\n")
print("Content-Type: text/plain", end="\r\n")
print("Content-Length: 27", end="\r\n")
print("", end="\r\n")
print("This is the pythonic CGI!", end="\r\n")
sys.stdout.close()
