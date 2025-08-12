#include <Arduino.h>

class WLAN {
  public:
    void begin();
    void begin(String mode="client");
    void begin(String mode="client", String ssid="default-ssid", String password="password123");
    void begin(String mode, String ssid, String password, IPAddress local_ip, IPAddress gateway, IPAddress subnet);
    void disconnect();
};