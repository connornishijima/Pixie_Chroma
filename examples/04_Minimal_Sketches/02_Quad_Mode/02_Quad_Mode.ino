// This is a bare-minimum Pixie Chroma sketch using Quad-GPIO mode!
// Use this template to easily build your own Pixie Chroma sketches.

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define PIXIES_PER_PIN  3 // Number of Pixie PCBs per GPIO
#define PIXIES_X        6 // Total amount and arrangement
#define PIXIES_Y        2 // of Pixie PCBs
                          //
                          // 4 lines with 3 Pixies == 12 total

// Quad Mode GPIO, same on ESP8266 and ESP32:

// DATA_OUT_1: GPIO 12 / D6
// DATA_OUT_2: GPIO 13 / D7
// DATA_OUT_3: GPIO 14 / D5
// DATA_OUT_4: GPIO 15 / D8

void setup() {
  pix.begin_quad( PIXIES_PER_PIN, PIXIES_X, PIXIES_Y );
  pix.color( CRGB::Cyan );
}

void loop() {
  pix.clear();
  pix.print( millis() );
  pix.show();
}