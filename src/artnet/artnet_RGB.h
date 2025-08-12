#include <Arduino.h>
#include "shared.h"

void setFrameOnArtnet(RGB** frame, ArtnetWifi& artnet, size_t frameWidth, size_t frameHeight);
void displayInit(size_t frameWidth, size_t frameHeight, ArtnetWifi& artnet);