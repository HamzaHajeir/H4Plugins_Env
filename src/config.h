#pragma once
#include <string>

#ifndef H4P_SECURE
#define H4P_SECURE 1
#endif

#define USE_MQTT 1
#define SECURE_WEBSERVER 0
#define SECURE_HTTPREQ 1

#if SECURE_HTTPREQ && !H4P_SECURE
#error "Activate H4P_SECURE if attempting to secure the HTTP requests"
#endif

#if SECURE_WEBSERVER && !H4P_SECURE
#error "Activate H4P_SECURE if attempting to secure the webserver"
#endif

const char *WIFI_SSID = "XXXXXXXX";
const char *WIFI_PASS = "XXXXXXXX";

#if H4P_SECURE
#if USE_MQTT
const char *MQTT_SERVER = "https://192.168.1.34:8883";
std::string MQTT_CERT = R"(-----BEGIN CERTIFICATE-----
MIIDgTCCAmmgAwIBAgIUQcIf6OLWUzmZb2mPVcyOMG1HRSkwDQYJKoZIhvcNAQEL
BQAwUDELMAkGA1UEBhMCSk8xDjAMBgNVBAgMBUFtbWFuMQ4wDAYDVQQHDAVBbW1h
bjELMAkGA1UECgwCSDQxFDASBgNVBAMMC0hhbXphSGFqZWlyMB4XDTIzMDYxMDE1
MjIyMFoXDTI0MDYwOTE1MjIyMFowUDELMAkGA1UEBhMCSk8xDjAMBgNVBAgMBUFt
bWFuMQ4wDAYDVQQHDAVBbW1hbjELMAkGA1UECgwCSDQxFDASBgNVBAMMC0hhbXph
SGFqZWlyMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAxY9hJHHvhG+5
/+OaybsHkik4YfX58wa0NhdmVDZLI9Z9s251r+ztQC0VC6e5mwS+W5UcZ9WYjYbN
HVM3f+dzgwOn9wsYTPWWTfIso02Z7lXcjhKcVlK9Bq3UeOBX103fFsS2rCCxy/pt
9EXA+95E2Pjps1nDyGjjvjUGkhiIe9NXV2+1aAJfDK/pWBjlDv8eqnhvq3pj2MM4
negYxMO9sqjOjfUkNAEG5jcDlMhHEdWoL7HyaKf8ddv8xtoqrPK7XJZ/32jp2PJd
lZbH6y/7b42Dn3wIFiNbviIaoDnOtUqFJMzB9WY9u4t6be/IX2eFttTXo233pVOF
N+2GA8n3HQIDAQABo1MwUTAdBgNVHQ4EFgQUCdpwdS001EQzEqznEZdJYASEHoQw
HwYDVR0jBBgwFoAUCdpwdS001EQzEqznEZdJYASEHoQwDwYDVR0TAQH/BAUwAwEB
/zANBgkqhkiG9w0BAQsFAAOCAQEAjioxltqlpw+qkWd2uELPbPPw9ctHU0RIjxLW
/1gNkYeetSnFlVO4XcraxSlmDgk5jd1whwlO1MCi6nwW6LJAVOxX/WXrefjfVN53
r7aWMhqI3cvDOyY6ishy+iImRzzJVyla+viAvyYGPlOuL2kctNOysk20N6ZcYTdQ
DfbEr0WRFQEC5NTIdxV/864pHYA9NrG4RAcEEJsTR0yJpj4GdmN1kkJj5DCEt4I4
XyMIsWKOK7LJV2KP3y/kFrQo1cxq9FR6Mw0oSsbcyffBzaGRt0YJO06dYsPzp4k5
l1Lth94UiX4BIGiaXx4FXRqpAzLQMwEWCS1XyJVrppom8Vo3WQ==
-----END CERTIFICATE-----
)";
#else // USE_MQTT
const char *MQTT_SERVER = "http://192.168.1.34:1883";
#endif // USE_MQTT

#if SECURE_WEBSERVER
std::string WEBSERVER_CERT = R"(-----BEGIN CERTIFICATE-----
MIIDczCCAlugAwIBAgIUTTk4lTotgitbnMP+Et/ehNdXOwEwDQYJKoZIhvcNAQEL
BQAwSTELMAkGA1UEBhMCSk8xDDAKBgNVBAgMA0FNTTEMMAoGA1UEBwwDQU1NMQsw
CQYDVQQKDAJINDERMA8GA1UEAwwISDRUZXN0ZXIwHhcNMjMwNjEwMTQwODI3WhcN
MjQwNjA5MTQwODI3WjBJMQswCQYDVQQGEwJKTzEMMAoGA1UECAwDQU1NMQwwCgYD
VQQHDANBTU0xCzAJBgNVBAoMAkg0MREwDwYDVQQDDAhINFRlc3RlcjCCASIwDQYJ
KoZIhvcNAQEBBQADggEPADCCAQoCggEBAL0NUrK9JrCHeosEk1aAPP+igwljqE2p
HHH738S8p1KvQNaRsEVOLnGrHc6oy1pEM55vk/Ag1QrEBaIbCWDQOsjfPi0KKlub
4nn5vCae32p58ZpNCIfE6KyHhHUXyTCIgOIwuSeVWYIhYE4aFrSJzo5lVa3hQzu4
AAFZtmT6pPf5ZkCgJjuvwCi1tmeBrb25wb4SU493I/zsY68Cu7Wugyoh2N9bnLyK
NlMy3xR8LHG21sqMWfOnRiqxp5LQh5GLY4huPfVW3/jJVX8cMt5FQP3lJFqMKr66
t1VqWXMk2eAxrcsKh8h08pAD2YGry0FseAMDnepOirZDOoI948qX3M8CAwEAAaNT
MFEwHQYDVR0OBBYEFEPjIgsZHRGxf8hvbarcVEOM9llzMB8GA1UdIwQYMBaAFEPj
IgsZHRGxf8hvbarcVEOM9llzMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQEL
BQADggEBAFPrDIrKb+jqbSunBbNzo7sgihjqYarKeEH3Cq7/QJ8XnvOlU/9puZSg
erHw+vhGe4UHSX+vOsBKvj9tzJUeTqHuzFFZRBHz1gWt+MIflHoSTqCt9oYfAT/S
s+Ld4sAumsg3KzoNQWjVLomAFvrgbIANuzGnT4hVbZPxxT8pr4knnCvpL87+5wy+
6RR8gy0JaWiZs21nYUjCf7oWtafI1yHjVhC+EIGet6x91GLTqnTD8EH8L/F6T92I
FHCgtCDKU1vTuKsLpxeiZCI0ju5cbc2//ZMim7Lz4Kk/BgwQBEfHD3AsSjh4LcI1
lejnr3NL/azDA4uulkfKlkOOgHT0j/Y=
-----END CERTIFICATE-----
)";
std::string WEBSERVER_PRIV_KEY = R"(-----BEGIN PRIVATE KEY-----
MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQC9DVKyvSawh3qL
BJNWgDz/ooMJY6hNqRxx+9/EvKdSr0DWkbBFTi5xqx3OqMtaRDOeb5PwINUKxAWi
Gwlg0DrI3z4tCipbm+J5+bwmnt9qefGaTQiHxOish4R1F8kwiIDiMLknlVmCIWBO
Gha0ic6OZVWt4UM7uAABWbZk+qT3+WZAoCY7r8AotbZnga29ucG+ElOPdyP87GOv
Aru1roMqIdjfW5y8ijZTMt8UfCxxttbKjFnzp0YqsaeS0IeRi2OIbj31Vt/4yVV/
HDLeRUD95SRajCq+urdVallzJNngMa3LCofIdPKQA9mBq8tBbHgDA53qToq2QzqC
PePKl9zPAgMBAAECggEARviochdWXfEOTQATu+Z6f9Fnde/mr/jrh9Lxp27XNdA6
/BJHZU07XErL7tgpNyLhafojRINe1yLNppSVybWCTASa19e4HRoBRJ8/RhRgdR2A
WNfQev+uBY7+Z+LdEY49LCz0ZWrI5nRXLhrXKUGOvKBIMPWfAt1Jizg9o90Ab2KY
mVMPQ3LbbvV+vC8Juh5EEaqEttgWCXlW8QwiGedFmW52UeF4cVMdJcuXxxZ7pLiz
AEs4AuULk43CWtdhwtyLG6VCzsZLl8SIG+cqYHuvYM9kB6IkQemOSs4e0oHQ0Ygd
Cxz1wm364T4ZF+m5DC1gMJTjAGY1fAyuqVEfjYcBiQKBgQDtj+vlBrkzD2DYDMhn
VBCjdv8vBkcZTs8lrJPyEmrUhOPOvm5SX3o+fdrbPSklCKjqb8ks/XciYavzeIDd
AtyimOHZG2VIRV401nq0nn8PaYZ9gukdSKxmSzNyWRZYu4Ow/dTzDrGxKSG6z5ED
MHE8t13x7Oelw0pkgJxVGPFp/QKBgQDLuZAB1W5uXSH9etOEmmtsdpmLDg3fRil5
dgNqG1491cLlbQB0HIih+GbYzvIGE40Oq8vMY7aEvChtP032w0R8PQhIzGfKz4ri
uOQwFAeqM8puSiUOhZ0bAHM3Id/wCeWzmTGI3rmN+MEnEmLb5lYYws6e6vuDdbOf
k5u+ApuFuwKBgFFgxdwUq4h0MiaQam4K/BAjCVNggSaIOqmbLqrz6CiYxTjjPwN0
tXmGv1vu3ZNUHhkA5hdFVHQwpSioFOyguFfyqxsmKVHSgWz0M+B/kuMCsRF5sMVZ
ScVY6Wy4W9FVms0chsAkPnaDsow94l0HUSMNZV8kWk4MUgWPkP4Np1U5AoGAKI0O
Kh9GtPcaze7F7Y4jNdrBo1kvz7KSjNe9xEAgWSSUf8Bbp8EKPVtJdXxz1lvL5xCx
J0Ttzqv5TA2ewjCKEETBwmPVgRwgpBJzcVJ7WBipAZ0GlUZpSDelt2KpxYjizQYA
QyM6QhUytUlGnkjR+GnGYQGbAMbL80aZaI/yTwMCgYBCzBPFPt7IsKDLSbCSmBwX
PgzoQBU0Z1kMFulTEbdaikMYwDP9spJrePSxS3KefltSo6fHz+W8fxKzgHql8l7v
yx1X4kTgIMK9wt96hW5lgZUyOZz/oSLO5YNuYT54DEs/HFWnX3s7HoeC0mC5qIIi
C+rU6AEiQVPvNQVim9/+4g==
-----END PRIVATE KEY-----
)";
#endif // SECURE_WEBSERVER

#if SECURE_HTTPREQ
// ISRG Root X1 certificate, the CA of Let's Encrypt
std::string test_root_ca = R"(-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)";
#endif // SECURE_HTTPREQ
#endif // H4P_SECURE

