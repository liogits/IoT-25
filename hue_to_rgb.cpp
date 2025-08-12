#include <Arduino.h>
#include <shared.h>

RGB hue_to_rgb(float h, float s, float v) {
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = v - c;

    float r1, g1, b1;

    if (h >= 0 && h < 60) {
        r1 = c; g1 = x; b1 = 0;
    } else if (h < 120) {
        r1 = x; g1 = c; b1 = 0;
    } else if (h < 180) {
        r1 = 0; g1 = c; b1 = x;
    } else if (h < 240) {
        r1 = 0; g1 = x; b1 = c;
    } else if (h < 300) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }

    RGB rgb;
    rgb.r = (int)((r1 + m) * 255);
    rgb.g = (int)((g1 + m) * 255);
    rgb.b = (int)((b1 + m) * 255);
    return rgb;
}