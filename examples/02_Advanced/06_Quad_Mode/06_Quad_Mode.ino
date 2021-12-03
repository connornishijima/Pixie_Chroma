/*----------------------------------------------------------------------------

  Pixie Chroma | 06_Quad_Mode.ino
  by Connor Nishijima Nov. 2021
  -------------------------------

  This sketch demonstrates "Quad Mode", which allows you to drive Pixie
  Chromas with 4 GPIO in parallel to increase speed! This requires different
  syntax and wiring:

  Syntax:
  
    pix.begin_quad( PIXIES_PER_GPIO, PIXIES_X, PIXIES_Y );

  WARNING: To use Quad Mode, your total number of Pixies should ideally be
  evenly divisible by 4. (e.g. 4, 8, 12, 16, 20, 24, etc.)

  For wiring, you'll need to know *how many Pixies there will be on each
  of the 4 chains. In the case of 12 Pixies (3 per line) in a 6x2 arrangement:

    pix.begin_quad( 3, 6, 2 );

  Unfortunately, this currently requires hard-coded pins to function *due to
  FastLED limitations*:

   Quad Mode GPIO:     ESP8266 / ESP32     TEENSY 3.X
   --------------------------------------------------
   DATA_OUT_1:         GPIO 12 / D6        GPIO 2
   DATA_OUT_2:         GPIO 13 / D7        GPIO 14
   DATA_OUT_3:         GPIO 14 / D5        GPIO 7
   DATA_OUT_4:         GPIO 15 / D8        GPIO 8

  See "WIRING" below for quad mode-specific hookup details.  

----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define PIXIES_PER_GPIO  3 // GPIO to use for Pixie Chroma data line
#define PIXIES_X  6        // Total amount and arrangement
#define PIXIES_Y  2        // of Pixie PCBs = 6 x 2
                           //
                           // See "WIRING" below!

void setup() {
  pix.begin_quad( PIXIES_PER_GPIO, PIXIES_X, PIXIES_Y );
  //  ^ QUAD MODE SPECIFIC
  // Initializes the displays, and sets things
  // like the default power budget for you.

  pix.clear(); // ................... Clears the display buffer
  pix.color( CRGB(255,0,64) ); // ... Sets the global color to *PINK*  
}

void loop() {
  pix.clear(); // ................... Clears the display buffer, 
  pix.println(pix.frame_rate); // ... prints the current frame rate (1 frame latency),
  pix.print("FRAMES / SEC"); // ..... a description, and
  pix.show(); // .................... sends the updated image to the Pixies.
  
  // REPEAT
}


/*################################# WIRING ###################################

  QUAD MODE WIRING GUIDE:
    
      DATA_OUT_1 --+              DATA_OUT_2 ----+
                   |                             |
                +--+-+   +----+   +----+  ||  +--+-+   +----+   +----+
                |  1 |-->|  2 |-->|  3 |  ||  |  4 |-->|  5 |-->|  6 | 
                +----+   +----+   +----+  ||  +----+   +----+   +----+ 
    
      DATA_OUT_3 --+              DATA_OUT_4 ----+
                   |                             |
                +--+-+   +----+   +----+  ||  +--+-+   +----+   +----+
                |  7 |-->|  8 |-->|  9 |  ||  | 10 |-->| 11 |-->| 12 | 
                +----+   +----+   +----+  ||  +----+   +----+   +----+ 

  WARNING: Always double-check your wiring! LEDs may be low power, but they
  are more-than-happy to burn themselves out if wired incorrectly!

  Each Pixie Chroma PCB has a gold arrow on its face, which points to the top
  of the PCB - shown here with a ^ character.

################################## WIRING ##################################*/