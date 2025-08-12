#include <Arduino.h>
#include <variables.h>
#include <shared.h>


void mergeFrame(RGB** dest, RGB** src_high, RGB** src_low, size_t frameWidth, size_t frameHeight) {
  //Serial.println("Merge Frame called");
  for (int x = 0; x < frameWidth; ++x) {
    for (int y = 0; y < frameHeight; ++y) {
      const RGB& high = src_high[x][y];
      const RGB& low = src_low[x][y];

      int brightness_high = high.r + high.g + high.b;
      int brightness_low = low.r + low.g + low.b;

      RGB result;

      if (brightness_high > brightness_low) {
          result = high;
      } else if (brightness_low > brightness_high) {
          result = low;
      } else {
          // Komponentenweise maximale Werte mischen
          result.r = std::max(high.r, low.r);
          result.g = std::max(high.g, low.g);
          result.b = std::max(high.b, low.b);
      }

      dest[x][y] = result;
    }
  }
}