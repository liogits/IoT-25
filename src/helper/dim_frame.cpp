#include <Arduino.h>
#include <variables.h>
#include <shared.h>

void dimFrame(RGB** frame, float dim_factor, size_t frameWidth, size_t frameHeight) {
  for (int x = 0; x < frameWidth; ++x) {
        for (int y = 0; y < frameHeight; ++y) {
            RGB& pixel = frame[x][y];

            pixel.r = static_cast<unsigned char>(pixel.r * dim_factor);
            pixel.g = static_cast<unsigned char>(pixel.g * dim_factor);
            pixel.b = static_cast<unsigned char>(pixel.b * dim_factor);
        }
    }
}