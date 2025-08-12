#include <Arduino.h>
#include <WiFi.h>
#include <wlan/wlan.h>


const char* ssid = "TP-Link-IoT25";
const char* password = "92585454";

bool state = true;
int i = 0;

void wifiInit() {
  WiFi.begin(ssid, password);
    Serial.println("");
    Serial.println("Connecting to WiFi");
    
    // Wait for connection
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (i > 20){
        state = false;
        break;
      }
      i++;
    }
    if (state) {
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(IPAddress(WiFi.localIP()));
    } else {
      Serial.println("");
      Serial.println("Connection failed.");
    }
}