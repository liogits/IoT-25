#include <Arduino.h>
#include <ArtnetWifi.h>
#include <shared.h>
#include <helper/helpers.h>

// Initialisiert das Display und setzt alle LEDs auf Schwarz
void displayInit(size_t frameWidth, size_t frameHeight, ArtnetWifi& artnet) {
  for (int i = 0; i <= frameWidth * frameHeight * COLOR_COUNT; i++) {
    if (i > 0) {
      artnet.setByte(i - 1, 0);
    }
    artnet.setByte(i, 255);
    artnet.write();
  }
}

// Iteriert über das Frame und setzt die RGB-Werte auf die entsprechenden Bytes im Artnet-Paket
void setFrameOnArtnet(RGB** frame, ArtnetWifi& artnet, size_t frameWidth, size_t frameHeight) {
  for (size_t y = 0; y < frameHeight; y++) {
    for (size_t x = 0; x < frameWidth; x++) {
      int index = y * frameWidth + x;
      artnet.setByte((index * 3), frame[x][y].r);
      artnet.setByte((index * 3) + 1, frame[x][y].g);
      artnet.setByte((index * 3) + 2, frame[x][y].b);
    }
  }

  // Sende das Artnet-Paket
  bool state = artnet.write();
  if (LOG_RENDERER) (!state) ? Serial.println("Artnet Error") : Serial.println("Artnet Sent");

}