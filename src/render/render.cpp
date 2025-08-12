#include <Arduino.h>
#include <variables.h>
#include <shared.h>
#include <render/render.h>
#include <helper/helpers.h>
#include <artnet/artnet_RGB.h>
#include <mappings/mappings.h>


// Renderer-Klasse
Renderer::Renderer(const char* name, const char host[], uint8_t universe, size_t frameWidth_, size_t frameHeight_)
  : taskName(name),   // Referenzen und Konstanten initialisieren
    frameWidth(frameWidth_),
    frameHeight(frameHeight_)
{
  // Artnet initialisieren
  artnet.begin(host);
  artnet.setLength(frameWidth * frameHeight * 3);
  artnet.setUniverse(universe);

  // Queue mit Platz für 16 MIDI-Events pro Renderer
  midiQueue = xQueueCreate(16, sizeof(MidiEvent));

  // Speicher für Frames allokieren
  allocateFrameNow();
  allocateFrameLast();
  allocateMidiData();

  // Alle LEDs des Renderers auf Schwarz setzen / Das Display initialisieren
  Serial.println("Starting Display Init...");
  delay(1000);
  displayInit(frameWidth, frameHeight, artnet);
}

// Getter für die MIDI-Queue
QueueHandle_t Renderer::getMidiQueue() {
    return midiQueue;
  }

// Startet den Renderer-Task
void Renderer::begin() {
  xTaskCreate(Renderer::renderTaskStatic, taskName, 4096, this, 1, &taskHandle);
}

// Statische Methode, die als Task-Einstiegspunkt dient
void Renderer::renderTaskStatic(void* param) {
  static_cast<Renderer*>(param)->renderTask();
}


// Haupt-Render-Task, der in einer Endlosschleife läuft
void Renderer::renderTask() {
  const TickType_t xDelay = FRAMETIME_IN_MS / portTICK_PERIOD_MS;

  while (true) {
    processMidiQueue();      // MIDI-Events abarbeiten
    renderFrame();     // Aktuellen Frame rendern

    vTaskDelay(xDelay);
  }
}


// Verarbeitet die MIDI-Queue und ruft onMidiNote für jedes Event auf
void Renderer::processMidiQueue() {
  MidiEvent event;
  while (xQueueReceive(midiQueue, &event, 0) == pdTRUE) {
      onMidiNote(event);
  }

}

void Renderer::onMidiNote(const MidiEvent& event) {
  if (event.noteOn) {
    if (LOG_RENDERER) {
      Serial.print("Note on: ");
      Serial.println(event.note);
    }

    switch (event.note){
      case 36: // Bassdrum
        getBassDrum(midiData, frameWidth, frameHeight, event);
        break;
      case 38: // Snaredrum
        getSnareDrum(midiData, frameWidth, frameHeight, event);
        break;
      case 42: // Hi-Hat
        getHiHat(midiData, frameWidth, frameHeight, event);
        break;
      case 48: // Tom
        getTom(midiData, frameWidth, frameHeight, event);
        break;
      default: // Unbekannte Note, leerer Frame
        getBlank(midiData, frameWidth, frameHeight, event);
        break;
    }
  } else if (!event.noteOn) {
    getBlank(midiData, frameWidth, frameHeight, event);
    if (LOG_RENDERER) {
      Serial.print("Note off: ");
      Serial.println(event.note);
    }
  }
}

void Renderer::allocateFrameNow() {
    frameNow = new RGB*[frameWidth];
    for (size_t x = 0; x < frameWidth; ++x) {
        frameNow[x] = new RGB[frameHeight];
        for (size_t y = 0; y < frameHeight; ++y) {
            frameNow[x][y] = {0, 0, 0};
        }
    }
}

void Renderer::allocateFrameLast() {
    frameLast = new RGB*[frameWidth];
    for (size_t x = 0; x < frameWidth; ++x) {
        frameLast[x] = new RGB[frameHeight];
        for (size_t y = 0; y < frameHeight; ++y) {
            frameLast[x][y] = {0, 0, 0};
        }
    }
}

void Renderer::allocateMidiData() {
    midiData = new RGB*[frameWidth];
    for (size_t x = 0; x < frameWidth; ++x) {
        midiData[x] = new RGB[frameHeight];
        for (size_t y = 0; y < frameHeight; ++y) {
            midiData[x][y] = {0, 0, 0};
        }
    }
}

void Renderer::renderFrame() {
    // Hier wird der aktuelle Frame gerendert

    // 1. Merge mit dem letzten Frame
    mergeFrame(frameNow, midiData, frameLast, frameWidth, frameHeight);

    // 2. aktuellen Frame via Artnet senden
    setFrameOnArtnet(frameNow, artnet, frameWidth, frameHeight);

    // 3. aktuellen Frame und DIM_FACTOR dimmen
    dimFrame(frameNow, DIM_FACTOR, frameWidth, frameHeight);

    // 4. Aktuellen Frame als letzten Frame speichern
    copyFrame(frameLast, frameNow, frameWidth, frameHeight);
}

