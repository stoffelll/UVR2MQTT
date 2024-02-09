# UVR2MQTT
Auslesen des DL-Busses der UVR1611 mit einem ESP8266 und weitergabe der Daten per MQTT

Libraries needed:
PubSubClient
ESP8266WiFi


Configuration needed:

1. Set pins used for DL-Bus
const byte dataPin = 2;
const byte interrupt = 2;

2. Set WiFi (SSID, PW) and MQTT data (server IP, PW, Username)

