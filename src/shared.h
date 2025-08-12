// shared.h
#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>
#include <variables.h>
#include <ArtnetWifi.h> 

struct RGB {
    int r, g, b;
};

enum class PatternType {
    SnareDrum,
    BassDrum,
    HiHat,
    Tom,
    undefined,
    zeros
};

typedef struct {
    uint8_t note;
    uint8_t velocity;
    uint8_t channel;
    bool noteOn; // true = NoteOn, false = NoteOff
} MidiEvent;

#endif