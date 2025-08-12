#include <Arduino.h>
#include <shared.h>

void getBassDrum(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event);
void getSnareDrum(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event);
void getHiHat(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event);
void getTom(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event);
void getBlank(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event);