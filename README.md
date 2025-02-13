**UVR2MQTT**  
Read values from DL-Bus of e.g. Technische Alternative UVR1611 or UVR16x2 with ESP8266/ESP32 and send them via MQTT

**Links**  
- https://github.com/Buster01/UVR2MQTT  
- https://www.mikrocontroller.net/topic/134862  
- https://www.ta.co.at/
- https://www.ta.co.at/sensoren/fts-dl  
- https://espeasy.readthedocs.io/en/latest/Plugin/P092_UVR1611.html
- https://espeasy.readthedocs.io/en/latest/Plugin/P092_UVR31.html  
- https://forum.arduino.cc/t/arduino-zur-messwerterfassung-an-uvr1611-regelung-heizung/59416/15  


**Libraries needed:**  
- PubSubClient
- ESP8266WiFi

**Configuration needed:**
- Set pins used for DL-Bus    
`const byte dataPin = 2;`  **IMPORTANT: you need to use "D4"-Pin (ESP8266) when you have set "dataPin = 2"**  
`const byte interrupt = 2;`  
- Set WiFi (SSID, PW) and MQTT data (server IP, PW, Username)  
--> UVR2MQTT.ino  
`const char* ssid = "tbd";  // Wifi SSID/Name`  
`const char* wlan_passwd = "tbd"; // Wifi Password/PSK`  
`char* esp_hostname = "DL2MQTT-GW"; // Hostname`  
--> MQTT.h  
`mqtt_client.connect("DL2MQTT-GW", "admin", "HomeAssistant");`  
--> Username: admin // Password: "HomeAssistant"

**Hardware:**
- Voltage divider needed (only blue part) for 12V-DL-Bus (like used in USV16x2):
![image](https://github.com/stoffelll/UVR2MQTT/assets/5340003/7d38cf28-da65-411f-b2ac-bb542ce24af8)  
**Voltage divider with resistor network (to resistors in a row to get 8k6 ohm resistance**  
![Voltage Divider](https://github.com/stoffelll/UVR2MQTT/assets/5340003/49053864-e07e-430d-9c87-4528ede80637)  

**connected to another DL-bus-sensor from Technische Alternative "FTS14-240DL"**  
![DL-Bus via other Sensor](https://github.com/stoffelll/UVR2MQTT/assets/5340003/fd853702-f24f-4b42-a9d9-8e9c598a7fe7)  
- yellow cable is ground/gnd/"GND-DL Bus"  
--> (I used a resistor network of two resistors, as I didn't had one 8k6 ohm resistor)
- red cable is DL/"DL Bus @ 12V"


**connection to ESP8266 - IMPORTANT: you need to use "D4" when you have set "dataPin = 2"**  
![ESP8266-Pins](https://github.com/stoffelll/UVR2MQTT/assets/5340003/68ffce30-d5c1-4c1e-b1d1-131500b444dc)  

**Output in MQTT:**  
MQTT: homeassistant/UVR16x2/Sensor1: 31.70 -> Vorlauf H-Box (Temperatur)  
MQTT: homeassistant/UVR16x2/Sensor2: 46.20 -> T-Warmwasser (Temperatur Brauchwasser)  
MQTT: homeassistant/UVR16x2/Sensor3: 31.40 -> Temp WT-H-Box (Temperatur)  
MQTT: homeassistant/UVR16x2/Sensor4: 31.40 -> T-Heizkreis Vorlauf 1 (Temperatur Heizung)  
MQTT: homeassistant/UVR16x2/Sensor5: 409.50 -> UNKLAR T-Kollektor -> nicht genutzt  
MQTT: homeassistant/UVR16x2/Sensor6: 409.50 -> UNKLAR T-Speicher Unten  
MQTT: homeassistant/UVR16x2/Sensor7: 31.60 -> T-Puffer mitte (T-Kühlpuffer/Heizpuffer mitte) -> abhängig von der eigenen Installation  
MQTT: homeassistant/UVR16x2/Sensor8: 409.50 -> UNKLAR T-Heizkreis Vorlauf 2 -> nicht genutzt  
MQTT: homeassistant/UVR16x2/Sensor9: 0.00 -> Smart Grid -> Messwert "Aus"  
MQTT: homeassistant/UVR16x2/Sensor10: 409.50 -> Vorlauf Kaskade -> nicht genutzt  
MQTT: homeassistant/UVR16x2/Sensor11: 28.90 -> Rücklauf H-Box  
MQTT: homeassistant/UVR16x2/Sensor12: 4.40 -> T-Außen (Temperatur)  
MQTT: homeassistant/UVR16x2/Sensor13: 32.40 -> T-Kühlpuffer/Heizpuffer  
MQTT: homeassistant/UVR16x2/Sensor14: 1.00 -> Freigabe -> Messwert "Ein"  
MQTT: homeassistant/UVR16x2/Sensor15: 1.00 -> EVU-aus/Mono  
MQTT: homeassistant/UVR16x2/Sensor16: 0.00 -> Abtaubetrieb -> Messwert "Aus"  
MQTT: homeassistant/UVR16x2/Ausgang1: 1 -> Pumpe H-Box 1  
MQTT: homeassistant/UVR16x2/Ausgang2: 0 -> Ventil-Warmwasser (vermutlich Umschaltventil zwischen WW und Heizung)  
MQTT: homeassistant/UVR16x2/Ausgang3: 1 -> Heizkreispumpe 1  
MQTT: homeassistant/UVR16x2/Ausgang4: 0 -> E-Heizpatrone  
MQTT: homeassistant/UVR16x2/Ausgang5: 0 -> WP-aus 5c 1 (Unklar)  
MQTT: homeassistant/UVR16x2/Ausgang6: 0 -> Solarpumpe  
MQTT: homeassistant/UVR16x2/Ausgang7: 0 -> Heizkreispumpe 2  
MQTT: homeassistant/UVR16x2/Ausgang8: 0 -> Mischer-Heizkreis 1 (vermutlich erhöhen oder reduzieren)  
MQTT: homeassistant/UVR16x2/Ausgang9: 0 -> Mischer-Heizkreis 1 (vermutlich erhöhen oder reduzieren)  
MQTT: homeassistant/UVR16x2/Ausgang10: 0 -> Mischer-Heizkreis 2 (vermutlich erhöhen oder reduzieren)  
MQTT: homeassistant/UVR16x2/Ausgang11: 0 -> Mischer-Heizkreis 2 (vermutlich erhöhen oder reduzieren)  
MQTT: homeassistant/UVR16x2/Ausgang12: 0 -> TB142 Kühlung  
MQTT: homeassistant/UVR16x2/Ausgang13: 0 -> Ventil Kühlung (wenn Kühlbetrieb aktiviert-> statt Heizen)  
MQTT: homeassistant/UVR16x2/Drehzahl1: 0  
MQTT: homeassistant/UVR16x2/Drehzahl2: 0  
MQTT: homeassistant/UVR16x2/Drehzahl3: 0  
MQTT: homeassistant/UVR16x2/Drehzahl4: 0  
MQTT: homeassistant/UVR16x2/RSSI: -53
