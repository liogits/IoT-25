// shared.cpp
#include "shared.h"

//RGB frameNow[FRAME_WIDTH][FRAME_HEIGHT];
//RGB frameLast[FRAME_WIDTH][FRAME_HEIGHT];
//RGB midiData[FRAME_WIDTH][FRAME_HEIGHT];
SemaphoreHandle_t midiMutex = nullptr;