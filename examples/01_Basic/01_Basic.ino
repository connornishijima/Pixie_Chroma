#include "Pixie_Chroma.h"
PixieChroma pix;

#define DATA_PIN 5
#define PIXIES_X 6
#define PIXIES_Y 1

void setup() {
  pix.begin(DATA_PIN, PIXIES_X, PIXIES_Y);
  pix.set_animation(ANIMATION_NULL);
}

void loop() {
  pix.clear();
  pix.set_cursor(0,0);
  pix.print(millis());
  delay(50);

  yield(); // Stupid ESP needs WDT check-in often to prevent LED flickering
}
