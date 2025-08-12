#include <./wlan_old.h>
#include <WiFi.h>

// connect to wifi – returns true if successful or false if not
void WLAN::begin() {
  bool state = WiFi.softAP("esp32-ap", NULL);
  Serial.println("");
  Serial.println("Starting Accesspoint");

  while (!state) {
    Serial.println("AP could not be started! ");
    delay(500);
    Serial.print(".");
    break;
  }
  Serial.println("AP running...");
}

void WLAN::begin(String mode, String ssid, String password)
{
  if (mode == "client") {
    WiFi.softAPdisconnect();
    bool state = true;
    int i = 0;
  
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


    
  } else if (mode == "ap") {
    bool state = WiFi.softAP(ssid, password);
    Serial.println("");
    Serial.println("Starting Accesspoint");

    while (!state) {
      Serial.println("AP could not be started! ");
      delay(500);
      Serial.print(".");
      break;
    }
    Serial.println("AP running...");
    Serial.print("Own IP Address:");
    Serial.println(IPAddress(WiFi.softAPIP()));

    Serial.print("SSID:");
    Serial.println(WiFi.softAPSSID());
    
  }
  else {
    Serial.println("");
    Serial.println("Choose between modes: client | ap");
  }
}

void WLAN::begin(String mode, String ssid, String password, IPAddress local_ip, IPAddress gateway, IPAddress subnet) {
  if (mode == "ap") {
    bool configured = WiFi.softAPConfig(local_ip, gateway, subnet);
    if (configured) {
      Serial.println("Accesspoint configured...");
    } else {
      Serial.println("AP uses standard values");
    }
  }

  begin(mode, ssid, password);

  
}

void WLAN::disconnect() {
  bool state = WiFi.isConnected();
  int i = 0;
  WiFi.disconnect();
  Serial.print("Disconneting");
  while (WiFi.status() == WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false;
      break;
    }
    i++;
  }
  Serial.println("Disconnected");
}