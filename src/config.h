#pragma once
#include <string>

#ifndef H4P_SECURE
#define H4P_SECURE 1
#endif

#define USE_MQTT 1
#define SECURE_WEBSERVER 0
#define SECURE_HTTPREQ 1

#if SECURE_HTTPREQ && !H4P_SECURE
#error "Activate H4P_SECURE if attempting secure HTTP requests"
#endif

#if SECURE_WEBSERVER && !H4P_SECURE
#error "Activate H4P_SECURE if attempting secure the webserver"
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
const char* test_root_ca= \
     "-----BEGIN CERTIFICATE-----\n" \
     "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n" \
     "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
     "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n" \
     "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n" \
     "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n" \
     "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n" \
     "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n" \
     "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n" \
     "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n" \
     "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n" \
     "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n" \
     "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n" \
     "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n" \
     "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n" \
     "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n" \
     "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n" \
     "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n" \
     "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n" \
     "-----END CERTIFICATE-----\n";
#endif // SECURE_HTTPREQ
#endif // H4P_SECURE

