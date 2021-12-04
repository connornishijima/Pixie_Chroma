// This is a bare-minimum Pixie Chroma sketch using single-GPIO mode!
// Use this template to easily build your own Pixie Chroma sketches.

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define DATA_PIN  12 // GPIO to use for Pixie Chroma data line
#define PIXIES_X  2  // Total amount and arrangement
#define PIXIES_Y  1  // of Pixie PCBs

void setup() {
  pix.begin( DATA_PIN, PIXIES_X, PIXIES_Y );
  pix.color( CRGB::Cyan );
}

void loop() {
  pix.clear();
  pix.print( millis() );
  pix.show();
}