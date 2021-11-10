/*----------------------------------------------------------------------------

  Pixie Chroma | 03_Set_Palette.ino
  by Connor Nishijima Nov. 2021
  ---------------------------------

  This sketch demonstrates the pix.set_brightness(level) function, which
  accepts a value between 0-255. The dimming involved uses "temporal dithering"
  to help preserve color quality at lower brightness levels.

----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define DATA_PIN  12 // GPIO to use for Pixie Chroma data line
#define PIXIES_X  2  // Total amount and arrangement
#define PIXIES_Y  1  // of Pixie PCBs = 2 x 1 
                     //
                     // See "WIRING" below!

void setup() {
  pix.begin( DATA_PIN, PIXIES_X, PIXIES_Y );
  // Initializes the displays, and sets things
  // like the default power budget for you. 

  pix.set_animation(ANIMATION_STATIC);
}

void loop() {
  // GRADIENT ---------------------------------------------------------------------------------------------  
  pix.clear(); // ................. Clears the display buffer and
  pix.set_palette( // ............. Sets the palette to 
    GRADIENT_BLACK_RED_BLACK // ... a predefined gradient
  );                         // ... in pixie_palettes.h
  pix.print(1.2345, 2); // ........ Print a floating point value, to two decimal places of precision and
  pix.show(); // .................. send the updated image to the Pixies.
  delay(1000);


  // RAINBOW ----------------------------------------------------------------------------------------------  
  pix.clear(); // ................ Clears the display buffer and
  pix.set_palette(RAINBOW); // ... sets the palette to a predefined color scheme from pixie_palettes.h.
  pix.print(4.5678, 2); // ....... Print a floating point value, to two decimal places of precision and
  pix.show(); // ................. send the updated image to the Pixies.
  delay(1000);


  // CUSTOM -----------------------------------------------------------------------------------------------
  pix.clear(); // ............ Clears the display buffer and
  pix.set_palette( // ........ Sets the palette to 
    make_gradient( // ........ a gradient generated at runtime from
      CRGB::Red,   // ........ red 
      CRGB::Blue  // ......... and blue.  
    )
  );
  pix.print(9.0123, 2); // ... Print a floating point value, to two decimal places of precision and
  pix.show(); // ............. send the updated image to the Pixies.
  delay(1000);

  // REPEAT
}

/*################################# WIRING ###################################

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

################################## WIRING ##################################*/