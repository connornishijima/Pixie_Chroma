/*----------------------------------------------------------------------------

  Pixie Chroma | 05_Manual_Color.ino
  by Connor Nishijima Nov. 2021
  ----------------------------------

  This sketch demonstrates the various coloring functions available if you
  want to manually manage color!

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

  pix.clear(); // .............. Clear the display buffer,
  pix.print( 1234 ); // ........ print a uint8_t value and...
}

void loop() {
  pix.color( CRGB::Red ); // ... Set the entire display to red, and
  pix.show(); // ............... send the updated image to the Pixies.
  delay(1000);

  pix.color( CRGB::Cyan, 0, 0 ); // ... Set a single display to cyan, and
  pix.show(); // ...................... send the updated image to the Pixies.
  delay(1000);

  pix.color( CRGB::Orange, 15, 4, 23, 10 ); //  Set a 2D rectangle from (15,4) to (23,10) to orange, and
  pix.show(); // .............................. send the updated image to the Pixies.
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