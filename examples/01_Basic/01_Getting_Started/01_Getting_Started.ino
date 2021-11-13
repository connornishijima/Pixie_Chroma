/*----------------------------------------------------------------------------

  Pixie Chroma | 01_Getting_Started.ino
  by Connor Nishijima Nov. 2021
  -------------------------------------

  Welcome to Pixie Chroma! This sketch will define the bare minimum of any
  Pixie Chroma Arduino code, including how to initialize your Pixie Chromas
  and print text to the display!

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
  
  pix.print( "HI [:HEART:]" ); // ... Print a char array with a Shortcode (see 02_Advanced/14_Shortcode_Library)
  pix.show(); // .................... Send all updates to the Pixie Chroma PCBs
}

void loop() {
  // Nothing to see here!
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