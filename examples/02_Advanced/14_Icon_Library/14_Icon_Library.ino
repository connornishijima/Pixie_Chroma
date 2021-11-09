// TODO: 14_Icon_Library.ino needs content

// TODO: Icon Generator needs to be fully ported from the original Pixie library to work with Pixie Chroma-format Icons and files

#include "Pixie_Chroma.h"
PixieChroma pix;

#define DATA_PIN	3
#define PIXIES_X	6
#define PIXIES_Y	2

void setup() {
  Serial.begin(250000);
  pix.begin(DATA_PIN, PIXIES_X, PIXIES_Y);
  delay(200);
}

void loop() {
  pix.clear();
}
