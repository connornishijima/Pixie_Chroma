/*----------------------------------------------------------------------------

  Pixie Chroma | 02_Set_Brightness.ino
  by Connor Nishijima Nov. 2021
  ------------------------------------

  This sketch demonstrates the pix.set_brightness(level) function, which
  accepts a value between 0-255. The dimming involved uses "temporal dithering"
  to help preserve color quality at lower brightness levels.

  ################################# WIRING ###################################

  GND ---------------+---------------------------+
                     |                           |
  DATA_PIN -------+  |  +-- VCC    +----------+  |  +-- VCC
                  |  |  |          |          |  |  |  
           +- - - | -|- | - - -+   |   +- - - | -|- | - - -+
           | ==== O  O  O ==== |   |   | ==== O  O  O ==== |
                     ^             |             ^          
           |                   |   |   |                   |
                  PIXIE 1          |          PIXIE 2       
           |                   |   |   |                   |
                                   |                        
           | ==== O  O  O ==== |   |   | ==== O  O  O ==== |
           +- - - | - - - - - -+   |   +- - - - - - - - - -+
                  |                |
                  +----------------+
               (DATA LINE TO NEXT PIXIE)

  WARNING: Always double-check your wiring! LEDs may be low power, but they
  are more-than-happy to burn themselves out if wired incorrectly!

  Each Pixie Chroma PCB has a gold arrow on its face, which points to the top
  of the PCB - shown here with a ^ character.

----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define DATA_PIN  12 // GPIO to use for Pixie Chroma data line
#define PIXIES_X  2  // Total amount and arrangement
#define PIXIES_Y  1  // of Pixie PCBs = 2 x 1

void setup() {
  pix.begin( DATA_PIN, PIXIES_X, PIXIES_Y );
  // Initializes the displays, and sets things
  // like the default power budget for you.

  pix.clear(); // ................... Clears the display buffer
  pix.color( CRGB(255,0,64) ); // ... Sets the global color to *PINK*  
}

void loop() {
  // FADE IN
  for(uint8_t i = 0; i < 255; i++){
    pix.clear(); // ............. Clears the display buffer
    pix.write(i); // ............ Write an integer
    pix.set_brightness(i); // ... Set the output brightness
    pix.show(); // .............. Send changes to the Pixie Chromas
    delay(1);
  }
  
  // FADE OUT
  for(uint8_t i = 255; i >= 1; i--){
    pix.clear(); // ............. Clears the display buffer
    pix.write(i); // ............ Write an integer
    pix.set_brightness(i); // ... Set the output brightness
    pix.show(); // .............. Send changes to the Pixie Chromas
    delay(1);
  }

  // REPEAT
}