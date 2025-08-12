#include <Arduino.h>
#include <shared.h>
#include <variables.h>
#include <helper/helpers.h>

/*
RGB snareDrum[FRAME_WIDTH][FRAME_HEIGHT];
RGB bassDrum[FRAME_WIDTH][FRAME_HEIGHT];
RGB hiHat[FRAME_WIDTH][FRAME_HEIGHT];
RGB tom[FRAME_WIDTH][FRAME_HEIGHT];
RGB zeros[FRAME_WIDTH][FRAME_HEIGHT];

const int RADIUS = 3;
const int CENTER_X = FRAME_WIDTH / 2;
const int CENTER_Y = FRAME_HEIGHT / 2;
const double THRESHOLD = 0.5;

String patternTypeToString(PatternType type) {
    switch (type) {
        case PatternType::SnareDrum: return "SnareDrum";
        case PatternType::BassDrum:  return "BassDrum";
        case PatternType::HiHat:     return "HiHat";
        case PatternType::Tom:       return "Tom";
        case PatternType::zeros:     return "zeros";
        default:                     return "undefined";
    }
}

void logPattern(PatternType type, RGB frame[FRAME_WIDTH][FRAME_HEIGHT]) {
  if (LOG_PATTERNSELECT) {
    Serial.print(patternTypeToString(type));
    Serial.println(": ");
    for (int i = 0; i < FRAME_WIDTH; i++) {
      for (int j = 0; j < FRAME_HEIGHT; j++) {
        Serial.print("r:");
        Serial.print(frame[i][j].r);
        Serial.print(" g:");
        Serial.print(frame[i][j].g);
        Serial.print(" b:");
        Serial.print(frame[i][j].b);
      }
      Serial.println();
    }
    Serial.println("END MAPPED DATA");
    Serial.println();
  }
}

void seedMappings() {
  // SEED SNARE
  for (int i = 0; i < FRAME_WIDTH; i++) {
    snareDrum[i][i].g = 255;
    snareDrum[i][i].b = 128;
  }

  //SEED BASS
  for (int i = 0; i < FRAME_WIDTH / 2; i++) {
    for (int j = 0; j < FRAME_HEIGHT / 2; j++) {
      bassDrum[i][j*2].b = 255;
    }
  }
  for (int i = FRAME_WIDTH / 2; i < FRAME_WIDTH; i++) {
    for (int j = 0; j < FRAME_HEIGHT / 2; j++) {
      bassDrum[i][j*2].b = 255;
    }
  }

  // SEED HIHAT
  for (int y = 0; y < FRAME_WIDTH; y++) {
    for (int x = 0; x < FRAME_HEIGHT; x++) {
      if (x == 0 || x == FRAME_HEIGHT - 1) {
        if (y >= 2 && y < FRAME_WIDTH - 2) {
          hiHat[y][x].g = 255;
        }
      }
      if (x == 1 || x == FRAME_HEIGHT - 2) {
        hiHat[y][x].g = 255;
      } 
    }
  }

  // SEED TOM
  for (int y = 0; y < FRAME_WIDTH; y++) {
    for (int x = 0; x < FRAME_HEIGHT; x++) {
      double dx = x - CENTER_X;
      double dy = y - CENTER_Y;
      double distance = std::sqrt(dx * dx + dy * dy);

      if (std::abs(distance - RADIUS) <= THRESHOLD) {
          tom[y][x].b = 255;
      } else {
          tom[y][x].b = 0;
      }
    }
  } 
};

void mapping(PatternType type, RGB** array) {
  switch (type)
  {
  case PatternType::BassDrum:
    logPattern(type, bassDrum);
    copyMidiFrame(array, bassDrum);
    break;
  case PatternType::SnareDrum:
    logPattern(type, snareDrum);
    copyMidiFrame(array, snareDrum);
    break;
  case PatternType::HiHat:
    logPattern(type, hiHat);
    copyMidiFrame(array, hiHat);
    break;
  case PatternType::Tom:
    logPattern(type, tom);
    copyMidiFrame(array, tom);
    break;
  case PatternType::undefined:
    logPattern(type, zeros);
    copyMidiFrame(array, zeros);
    break;
  case PatternType::zeros:
    logPattern(type, zeros);
    copyMidiFrame(array, zeros);
    break;
  default:
    for (int i = 0; i < FRAME_WIDTH; i++) {
        for (int j = 0; j < FRAME_HEIGHT; j++) {
          array[i][j].r = 0;
          array[i][j].g = 0;
          array[i][j].b = 0;
        }
      }
    break;
  }
}
*/