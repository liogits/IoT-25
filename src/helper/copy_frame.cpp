#include <variables.h>
#include <shared.h>

void copyFrame(RGB** dest, RGB** src, size_t frameWidth, size_t frameHeight) {
  for (size_t x = 0; x < frameWidth; ++x) {
            for (size_t y = 0; y < frameHeight; ++y) {
                dest[x][y] = src[x][y];
            }
        }
}
