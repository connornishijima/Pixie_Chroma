// TODO: 11_XY_and_UV.ino needs content

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