#include <Arduino.h>
#include <shared.h>
#include <mappings/mappings.h>
#include <helper/helpers.h>
#include <render/render.h>

// Anzeigen, dass Renderer1 und Renderer2 existieren
extern Renderer* renderer1;
extern Renderer* renderer2;

// MIDI-Callback-Funktionen
// Diese Funktion wird aufgerufen, wenn eine Note-On-MIDI-Message empfangen wird
void onNoteOn(byte channel, byte pitch, byte velocity) {
  if (LOG_MIDI) {
    Serial.print("MIDI NOTE ");
    Serial.print(pitch);
    Serial.println(" ON");
  }

  if (renderer1 != nullptr && RENDERER1) {
        MidiEvent event = {pitch, velocity, channel, true};
        bool state = xQueueSend(renderer1->getMidiQueue(), &event, 0);
        if (!state) {
            Serial.println("Failed to send MIDI event to renderer1");
        }
    }
  
  if (renderer2 != nullptr && RENDERER2) {
        MidiEvent event = {pitch, velocity, channel, true};
        bool state = xQueueSend(renderer2->getMidiQueue(), &event, 0);
        if (!state) {
            Serial.println("Failed to send MIDI event to renderer2");
        }
    }
}

// Diese Funktion wird aufgerufen, wenn eine Note-Off-MIDI-Message empfangen wird
void onNoteOff(byte channel, byte pitch, byte velocity) {
  if (LOG_MIDI) {
    Serial.print("MIDI NOTE ");
    Serial.print(pitch);
    Serial.println(" OFF");
  }

  if (renderer1 != nullptr && RENDERER1) {
      MidiEvent event = {pitch, velocity, channel, false};
      bool state = xQueueSend(renderer1->getMidiQueue(), &event, 0);
      if (!state) {
          Serial.println("Failed to send MIDI event to renderer1");
      }
  }

  if (renderer2 != nullptr && RENDERER2) {
      MidiEvent event = {pitch, velocity, channel, false};
      bool state = xQueueSend(renderer2->getMidiQueue(), &event, 0);
      if (!state) {
          Serial.println("Failed to send MIDI event to renderer2");
      }
  }
}
