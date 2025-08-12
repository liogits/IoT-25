#include <Arduino.h>
#include <ArtnetWifi.h>
#include <shared.h>
#include <helper/helpers.h>

void artnetInit(size_t frameWidth, size_t frameHeight, ArtnetWifi& artnet) {
  for (int i = 0; i <= frameWidth * frameHeight * COLOR_COUNT; i++) {
    if (i > 0) {
      artnet.setByte(i - 1, 0);
    }
    artnet.setByte(i, 255);
    artnet.write();
  }
}

void artnetClearRGB(u_int8_t start_channel, ArtnetWifi& artnet) {
  for (int i = 0; i < 3; i++) {
    artnet.setByte(start_channel + i, 0);
  }
  artnet.write();
}

void setFrameOnArtnet(RGB** frame, ArtnetWifi& artnet, size_t frameWidth, size_t frameHeight) {
  //logFrameSerial(frame, frameWidth, frameHeight);
  for (size_t y = 0; y < frameHeight; y++) {
    for (size_t x = 0; x < frameWidth; x++) {
      int index = y * frameWidth + x;
      artnet.setByte((index * 3), frame[x][y].r);
      artnet.setByte((index * 3) + 1, frame[x][y].g);
      artnet.setByte((index * 3) + 2, frame[x][y].b);
    }
  }
  bool state = artnet.write();
  if (LOG_RENDERER) (!state) ? Serial.println("Artnet Error") : Serial.println("Artnet Sent");

}