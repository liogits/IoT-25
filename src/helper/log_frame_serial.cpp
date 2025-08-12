#include <variables.h>
#include <shared.h>

void logFrameSerial(RGB** frame, size_t frameWidth, size_t frameHeight) {
  Serial.println();
  Serial.println("LOG FRAME:");
  for (int i = 0; i < frameWidth; i++) {
    for (int j = 0; j < frameHeight; j++) {
      Serial.print("r:");
      Serial.print(frame[i][j].r);
      Serial.print(" g:");
      Serial.print(frame[i][j].g);
      Serial.print(" b:");
      Serial.print(frame[i][j].b);
    }
    Serial.println();
  }
  Serial.println("END FRAME");
  Serial.println();
}