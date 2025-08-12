#include <Arduino.h>
#include <shared.h>

void getBassDrum(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event) {
  for (int y = 0; y < frameHeight; y++) {
    for (int x = 0; x < frameWidth; x++) {
      if (x % 2 == 0) {
        array[x][y].b = 255; // Set blue color for bass drum
      } else {
        array[x][y] = {0, 0, 0}; // Set other pixels to black
      }
    }
  }
}

void getSnareDrum(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event) {
  // Implementierung für Snaredrum
  for (int y = 0; y < frameHeight; y++) {
    for (int x = 0; x < frameWidth; x++) {
      if (y > 2 || y < frameHeight - 2) {
        if (x % 2 == 1) {
          array[x][y].r = event.velocity * 2; // Set red color for snare drum
        } else {
          array[x][y] = {0, 0, 0}; // Set other pixels to black
        }
      }
      
    }
  }
  
  
  
  
  /* for (int i = 0; i < frameWidth; ++i) {
    if (i < frameHeight) {
      array[i][i] = {0, 255, 128}; // Set green and light blue for snare drum
    } else {
      array[i][i] = {0, 0, 0}; // Set other pixels to black if out of bounds
    }
  }
    */
}

void getHiHat(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event) {
  for (int y = 0; y < frameHeight; y++) {
    for (int x = 0; x < frameWidth; x++) {
      if (y == 0 || y == frameHeight - 1) {
        if (x >= 2 && x < frameWidth - 2) {
          array[x][y] = {event.velocity * 2, event.velocity * 2, 0}; // Set yellow for hi-hat
        }
      }
      if (y == 1 || y == frameHeight - 2) {
        array[x][y] = {event.velocity * 2, event.velocity * 2, 0}; // Set yellow for hi-hat
      } 
    }
  }
}

void getTom(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event) {
  for (int y = 0; y < frameHeight; y++) {
    for (int x = 0; x < frameWidth; x++) {
      if (y > 2 && y < frameHeight - 3) {
        if (x >= 2 && x < frameWidth - 2) {
          array[x][y] = {0, event.velocity * 2, 0}; // Set green Tom Body
        }
      }
      if (y >= frameHeight - 3) {
        if (x >= 2 && x < frameWidth - 2) {
          if (x % 2 == 0) {
            array[x][y].g = event.velocity * 2; // Set green for Tom Stands
          } else {
            //array[x][y] = {0, 0, 0}; // Set other pixels to black
          }
        }
      }
    }
  }


  /*
  const int RADIUS = 4;
  const int CENTER_X = frameWidth / 2.0;
  const int CENTER_Y = frameHeight / 2.0;
  const double THRESHOLD = 0.5;
  // Implementierung für Tom
  for (int y = 0; y < frameHeight; ++y) {
    for (int x = 0; x < frameWidth; ++x) {
      double dx = x - CENTER_X;
      double dy = y - CENTER_Y;
      double distance = std::sqrt(dx * dx + dy * dy);

      if (std::abs(distance - RADIUS) <= THRESHOLD) {
          array[x][y].b = 255;
      } else {
          array[x][y].b = 0;
      }
    }
  } 
  */
}

void getBlank(RGB** array, size_t frameWidth, size_t frameHeight, MidiEvent event) {
  for (int y = 0; y < frameHeight; y++) {
    for (int x = 0; x < frameWidth; x++) {
      array[x][y] = {0, 0, 0}; // Set all pixels to black
    }
  }
}
