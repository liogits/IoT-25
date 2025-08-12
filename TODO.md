# TODO

## MIDI

### Receiver
- Daten auf Message-Types zerlegen
  - Error werfen wenn Message nicht passt
- Funktion ausführen, wenn MIDI-Msg passt

### Mapping
- eine bestimmte Note entspricht einem bestimmten Bild/Array, dass dann dem Renderer gegeben werden kann
- Mappings erstmal fest definiert
  - Pixel-Daten von Jerry erarbeiten
- evtl auch als 64x64x3 hochladbar?
- Farbe trennbar von Bild?

## Netzwerk
[x] NW aufsetzen und alle Clients verbinden


## Renderer
- aktuelles MIDI-Array möglichst schnell auslesen, zwischenspeichern
- aktuelles MIDI-Array mit vorhergehendem Array mergen, wenn neue Daten vorhanden.
  - Alle höheren Werte ersetzen, niedrigere Werte auslassen
- aktuelles Array lesen, ausgeben
- ausgegebenes Array um Dimming-Wert vermindern
- bekommt man das in eine Klasse? so dass man mehrere Renderer erzeugen kann?




## Threading
- Threadingfunktionen aufsetzen
- gemeinsame Arrays (aktuelle, vorher, neue Daten) erzeugen
  - Die Arrays haben die größe WIDHTxHEIGHTx3 für die Pixel und 3 RGB-Werte



