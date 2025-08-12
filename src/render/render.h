#pragma once
#include <ArtnetWifi.h>
#include <Arduino.h>
#include <variables.h>
#include <shared.h>

class Renderer {
public:
  Renderer(const char* name, const char host[], uint8_t universe,  size_t frameWidth, size_t frameHeight);
  void begin();
  void updateFrameToRender(RGB** frame);
  void onMidiNote(const MidiEvent& event);
  QueueHandle_t getMidiQueue();
  void processMidiQueue();

  void allocateFrameNow();
  void allocateFrameLast();
  void allocateMidiData();

  void freeFrame();
  void renderFrame();

private:
  static void renderTaskStatic(void* param);
  void renderTask();

  ArtnetWifi artnet;
  RGB** frameNow;
  RGB** frameLast;
  RGB** midiData;

  size_t frameWidth;
  size_t frameHeight;

  QueueHandle_t midiQueue;

  SemaphoreHandle_t midiMutex;
  TaskHandle_t taskHandle;
  const char* taskName;
};

void mergeFrame(RGB** dest, const RGB** src_high, const RGB** src_low, size_t frameWidth, size_t frameHeight);
void dimFrame(RGB** frame, float dim_factor, size_t frameWidth, size_t frameHeight);