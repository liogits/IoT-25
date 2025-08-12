#include <Arduino.h>
#include <shared.h>

void copyFrame(RGB** dest, RGB** src, size_t frameWidth, size_t frameHeight);
void logFrameSerial(RGB** frame, size_t frameWidth, size_t frameHeight);
void mergeFrame(RGB** dest, RGB** src_high, RGB** src_low, size_t frameWidth, size_t frameHeight);
void dimFrame(RGB** frame, float dim_factor, size_t frameWidth, size_t frameHeight);
