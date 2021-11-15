/*----------------------------------------------------------------------------

  Pixie Chroma | 08_Power_Budgeting.ino
  by Connor Nishijima Nov. 2021
  -------------------------------------

  This sketch demonstrates automatic power budget restriction. By default,
  the Pixie Chroma library tries to keep total power consumption below 500mA.

  This is achieved via FastLED, which can calculate how far beyond a certain
  power budget your requested image is, and globally dim it until you're back
  under that budget.

  This sketch sets a max budget of 200mA at 5V, then begins to fill each pixel
  with pure white. As the display fills up, you'll notice that it
  automatically becomes darker to maintain color while reducing power
  requirements as more white LEDs are added!

  This way, you can know you'll keep your PC USB ports or decicated power
  supply within its limits no matter what you try to display on it!

  (The power budget defaults to 5V, 500mA)
  
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

  pix.clear(); // ........................ Clears the display buffer,
  pix.color( CRGB( 255,255,255 ) ); // ... sets the Color Map to pure white, and
  pix.set_max_power( 5.0, 200 ); // ...... sets the max power budget to 5.0V, 200mA. (Default 5V, 500mA)
}

void loop() {
  // This loop slowly fills the entire display with white pixels
  pix.clear();
  for(uint16_t y = 2; y < pix.matrix_height; y++){
    for(uint16_t x = 0; x < pix.matrix_width; x++){
      pix.mask[ pix.xy(x,y) ] = 255; // Manually setting mask transparency (255 = clear)
      pix.show();
      delay(25);
    }
  }

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