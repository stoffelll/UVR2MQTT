WiFiClient wlanClient;
PubSubClient mqtt_client(wlanClient);


boolean mqtt_connect(void) {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  } else {
    int counter = 0;
  
    mqtt_client.setServer(mqtt_server, 1883);
    //mqtt_client.setCallback(callback);
    
    //mqtt_client.connect("BL-NET");
    mqtt_client.connect("DL2MQTT-GW", "admin", "HomeAssistant");
    Serial.print("MQTT Connection: ");
    while (!mqtt_client.connected()) 
    {
      delay(500);
      Serial.print(".");
      counter++;
      if (counter > 15 ) {
        Serial.println("Verbindung konnte nicht aufgebaut werden!");
        ESP.reset();
        delay(2000);
        return false;
      }
    }
    Serial.println ("OK");
    return true;
  }
}

void mqtt_daten_senden() {
  Serial.println ("MQTT - Senden!");
  String topic = "";

  // Sensordaten über mqtt versenden
  for (int sv = 1; sv <= 16; sv++) {
    if (mqtt_client.connected()) {
      topic = "homeassistant/UVR16x2/Sensor" + String(sv);
      Serial.println("MQTT: " + topic + ": "+ String(SensorValue[sv]));
      mqtt_client.publish(topic.c_str(), SensorValue[sv].c_str());
    } 
    else {
      mqtt_connect();
    }
  }
  //if (mqtt_client.connected()) {
  //Wärmemengenzähler über mqtt versenden
  Serial.println("Waermemengenzähler");
  Serial.println("homeassistant/UVR16x2/WMZ1currentPower" + String(WMZ1[1].c_str()));
    mqtt_client.publish("homeassistant/UVR16x2/WMZ1currentPower", WMZ1[1].c_str());

  Serial.println("homeassistant/UVR16x2/WMZ1kwh" + String(WMZ1[2].c_str()));
    mqtt_client.publish("homeassistant/UVR16x2/WMZ1kwh", WMZ1[2].c_str());

  Serial.println("homeassistant/UVR16x2/WMZ1mwh" + String(WMZ1[3].c_str()));
    mqtt_client.publish("homeassistant/UVR16x2/WMZ1mwh", WMZ1[3].c_str());

  Serial.println("homeassistant/UVR16x2/WMZ2currentPower" + String(WMZ2[1].c_str()));
    mqtt_client.publish("homeassistant/UVR16x2/WMZ2currentPower", WMZ2[1].c_str());

  Serial.println("homeassistant/UVR16x2/WMZ2kwh" + String(WMZ2[2].c_str()));
    mqtt_client.publish("homeassistant/UVR16x2/WMZ2kwh", WMZ2[2].c_str());

  Serial.println("homeassistant/UVR16x2/WMZ2mwh" + String(WMZ2[3].c_str()));
    mqtt_client.publish("homeassistant/UVR16x2/WMZ2mwh", WMZ2[3].c_str());
  //} 
  //else {
  //    mqtt_connect();
  //  }

  // Zustände der Ausgänge übertragen
  for (int sv = 1; sv <= 16; sv++) {
    if (mqtt_client.connected()) {
      topic = "homeassistant/UVR16x2/Ausgang" + String(sv);
      Serial.println("MQTT: " + topic + ": "+ Ausgang[sv]);
      mqtt_client.publish(topic.c_str(), Ausgang[sv]? "1" : "0");
    } 
    else {
      mqtt_connect();
    }
  }

  // Drehzahl Ausgänge übertragen
  if (mqtt_client.connected()) {
    for (int sv = 1; sv <= 4; sv++) {
      topic = "homeassistant/UVR16x2/Drehzahl" + String(sv);
      Serial.println("MQTT: " + topic + ": "+ Drehzahl[sv]);
      mqtt_client.publish(topic.c_str(), Drehzahl[sv].c_str());
    } 
  } else {
      mqtt_connect();
    }

  // WLAN RSSI
  if (mqtt_client.connected()) {
    rssi = WiFi.RSSI();
    topic = "homeassistant/UVR16x2/RSSI";
    Serial.println("MQTT: " + topic + ": "+ rssi);
    mqtt_client.publish(topic.c_str(), rssi.c_str());
  } else {
      mqtt_connect();
    }
}
