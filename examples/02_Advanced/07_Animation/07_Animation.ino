/*----------------------------------------------------------------------------

  Pixie Chroma | 07_Animation.ino
  by Connor Nishijima Nov. 2021
  -------------------------------

  This sketch demonstrates preset Animations, which are used on each frame to
  influence the Color Map or Mask.
  
  Without defining a preset, the animation used is a function called
  ANIMATION_NULL(), which does nothing and requires you to use functions like
  pix.color() to change the display colors. 

  By defining an Animation, you leave color control up to automation, with a
  combination of the palette you have selected, and the animation that
  influences it. To use palettes without animation/movement, use:

  pix.set_animation(ANIMATION_STATIC);
  
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

  pix.clear(); // ................ Clears the display buffer  
  pix.set_palette(RAINBOW); // ... Sets the color palette to a preset RAINBOW

  pix.set_animation(ANIMATION_PENDULUM);
  // Set the animation to a "PENDULUM" preset, which uses a sine function
  // to swing the current palette left and right at 1Hz.
  //
  // All animation presets available are in src/utility/pixie_animations.h
}

void loop() {
  pix.clear(); // ................. Clears the display buffer  ,
  pix.print("HI [:HEART:]"); // ... prints a string with a Shortcode (See 02_Advanced\14_Shortcode_Library), and
  pix.show(); // .................. sends the updated image to the Pixies.

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