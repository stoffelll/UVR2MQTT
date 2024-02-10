
const byte dataPin = 2; 
const byte interrupt = 2;
int upload_interval = 60000;
const int additionalBits = 0;
int beginn = millis();
String SensorValue[17];
String WMZ1[3];
String WMZ2[3];
bool Ausgang[14];
String Drehzahl[5];
String rssi;

const char* ssid = "tbd";  // SSID deines WLAN Netzwerkes
const char* wlan_passwd = "tbd"; // Passwort deines WLAN Netzwerkes
char* esp_hostname = "DL2MQTT-GW";

const char* mqtt_server = "192.168.2.2"; // MQTT Server

extern "C" { 
  #include "user_interface.h" 
  }

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "receive.h"
#include "process.h"
#include "dump.h"
#include "MQTT.h"


void setup() {
  wifi_station_set_hostname(esp_hostname);
  WiFi.mode(WIFI_AP);
  Serial.begin(115200);
  WiFi.begin(ssid, wlan_passwd);
  
  byte WifiatemptCount = 0;
	while ((WiFi.status() != WL_CONNECTED) && (WifiatemptCount <= 10)) {
    String myString = String(WifiatemptCount);
		Serial.print(myString + "...");
		delay(500);
		WifiatemptCount++;
	}

  // WLAN Verbindung
  if (WiFi.status() != WL_CONNECTED) {
      Serial.println ("WLAN Verbindung fehlgeschlagen!");
      Serial.println ("Reset!");
      delay(2000);
      ESP.reset();
    } else {
      Serial.println();
      Serial.print("Verbindung! RSSI: "); Serial.print(WiFi.RSSI()); Serial.println(" dBi");
      Serial.print("IP-Adresse: "); Serial.println(WiFi.localIP());
      delay(2000);
    }
  Receive::start();
}

void loop() {
  if (mqtt_client.connected()) {
    mqtt_client.loop();
  }
  if (!Receive::receiving) {
    Process::start(); // Daten auswerten // process data
    Receive::start(); // Daten sammeln // receive data
  }
  if (millis() - beginn > upload_interval) {
    if (mqtt_connect()) {
      mqtt_daten_senden();
      beginn=millis();
    }
  }
}

