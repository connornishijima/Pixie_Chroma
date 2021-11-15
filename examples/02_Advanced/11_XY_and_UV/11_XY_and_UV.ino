/*----------------------------------------------------------------------------

  Pixie Chroma | 11_XY_and_UV.ino
  by Connor Nishijima Nov. 2021
  ----------------------------------

  This sketch demonstrates accessing the Mask or Color Map using both XY
  coordinates (whole pixel positions) or an OpenGL-style UV system like so:

  +-------------------+
  |0, 1           1, 1|
  |                   |
  |^                  |
  |                   |
  |0, 0     >     1, 0|
  +-------------------+

  Writing directly to the Color Map:
      pix.color_map[ pix.xy(  3,   5) ] = (CRGB) color; // Using XY Coords
      pix.color_map[ pix.uv(0.0, 1.0) ] = (CRGB) color; // Using UV Coords

  Writing directly to the Mask:
      pix.mask[ pix.xy(  3,   5) ] = (uint8_t) mask_transparency; // Using XY Coords
      pix.mask[ pix.uv(0.0, 1.0) ] = (uint8_t) mask_transparency; // Using UV Coords

  Both xy() and uv() take an (optional) bool as a third parameter, "wrap". If
  wrap is true, coordinated requested outside of the matrix will wrap to the
  opposite edge.

  NOTE: Pixie Chroma uses "invisible" pixels acting as padding between displays,
  to allow for spatial consistency. (i.e. If a word starts to scroll off the
  left side of one display, it will enter an "invisible" margin before it
  arrives on the next display. Because of this, the first "VISIBLE" pixel in a
  single Chroma PCB is at (1,2). Setting the color/mask at (0,0) will not be
  visible to the user.
  
  X = Visible
  . = Invisible

  | -------- PIXIE 1 -------- | -------- PIXIE 2 -------- |
   . . . . . . . . . . . . . . . . . . . . . . . . . . . .
   . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
   . X X X X X . . X X X X X . . X X X X X . . X X X X X . 
   . X X X X X . . X X X X X . . X X X X X . . X X X X X . 
   . X X X X X . . X X X X X . . X X X X X . . X X X X X . 
   . X X X X X . . X X X X X . . X X X X X . . X X X X X . 
   . X X X X X . . X X X X X . . X X X X X . . X X X X X . 
   . X X X X X . . X X X X X . . X X X X X . . X X X X X . 
   . X X X X X . . X X X X X . . X X X X X . . X X X X X . 
   . . . . . . . . . . . . . . . . . . . . . . . . . . . .
   . . . . . . . . . . . . . . . . . . . . . . . . . . . .

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

  pix.color(CRGB::Orange); // .......... Set color to ORANGE
  pix.set_gamma_correction(true); // ... Enable gamma correction
}

void loop() {
  // This function generates UV coordinates
  // that smoothly drift around over time
  static float iter = 0;  
  float x = (((sin(iter*0.111)+1)/2.0)*0.75)+0.125;
  float y = (((cos(iter*0.234)+1)/2.0)*0.50)+0.250;
  iter+=0.25;

  pix.dim(8); // ...................... Fade the mask by 8/256ths
  pix.mask[ pix.uv(x,y) ] = 255; // ... Show the drifting dot with UV coords
  pix.mask[ pix.xy(1,2) ] = 255; // ... Light up the first visible LED with XY coords
  pix.show(); // ...................... Send the updated image to the Pixies

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