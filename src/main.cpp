#include <Arduino.h>
#include <artnet/artnet_RGB.h>
#include "wlan/wlan.h"
#include <MIDI.h>
#include <helper/helpers.h>
#include <shared.h>
#include <midi/midi.h>
#include <variables.h>
#include <mappings/mappings.h>
#include <render/render.h>

// Speicher für Renderer-Instanzen
Renderer* renderer1;
Renderer* renderer2;


// MIDI-Instanz erstellen, Default-GPIOs für Serial2: RX=16, TX=17
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midiSerial);

// Host-Adressen für Renderer
const char host1[] = "172.16.0.50";
const char host2[] = "172.16.0.52"; 


// Loop-Funktion für MIDI-Erkennung, wird in Thread ausgeführt
void midiTask(void* param) {
  TickType_t xDelay = 1 / portTICK_PERIOD_MS;

  if (MIDI_TEST_DATA) {
    xDelay = 1000 / portTICK_PERIOD_MS;
  };

  while (true) {
    if (MIDI_TEST_DATA) {
      onNoteOn(1, random(33, 37), 127);
      vTaskDelay(xDelay);
    } else {
      midiSerial.read();
      vTaskDelay(xDelay);
    }
  }
};

void setup() {
  // Serielles Logging starten
  Serial.begin(115200);

  //WLAN AP aufsetzen, Settings in wlan/wlan.cpp
  wifiInit();

  // MIDI intialisieren
  midiSerial.setHandleNoteOn(onNoteOn);
  midiSerial.setHandleNoteOff(onNoteOff);
  midiSerial.begin(MIDI_CHANNEL_OMNI);
  Serial2.begin(31250, SERIAL_8N1, 16, 17); // RX, TX

  // Starte MIDI-Task auf Core 0
  xTaskCreatePinnedToCore(&midiTask, "MIDITask", 4096, nullptr, 1, nullptr, 0);

  if (RENDERER1) {  // Renderer1 initialisieren und starten
    renderer1 = new Renderer("Renderer1", host1, 1, 9, 13);
    renderer1->begin();
  }

  if (RENDERER2) {  // Renderer2 initialisieren und starten
    renderer2 = new Renderer("Renderer2", host2, 1, 9, 9);
    renderer2->begin();
  }


}

void loop() {
  // diese loop-Funktion bleibt leer, da die Tasks auf Threads verteilt werden

}

