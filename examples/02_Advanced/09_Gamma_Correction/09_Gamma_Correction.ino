/*----------------------------------------------------------------------------

  Pixie Chroma | 09_Gamma_Correction.ino
  by Connor Nishijima Nov. 2021
  --------------------------------------

  This sketch demonstrates the (optional) use of gamma correction. Gamma
  correction is used in displays like monitors or TVs to counteract the
  non-linear sensitivity of the human eye to brightness changes. Instead of
  describing at length here, I'll forward you to an Adafruit article that 
  explains it very well:

  Adafruit | LED Tricks: Gamma Correction
  https://learn.adafruit.com/led-tricks-gamma-correction

  By using pix.set_gamma_correction( true/false ); you can switch the effect
  on and off. With proper gamma correction, the green to black gradient
  below should appear completely black by the end of the display.

  WARNING: The current gamma correction algorithm used is slight unfriendly
  to "secondary" colors of light, such as Yellow, Magenta and Cyan. If used
  with these colors, they can appear much less intense than they should. If
  any lovely Pixie Chroma users have better algorithms for this, feel free to
  submit a pull request! Luckily, in most cases you won't really need gamma
  correction anyways to enjoy the look of your Pixies.
  
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

  pix.clear(); // ....... Clears the display buffer, and
  pix.set_palette( // ... sets the Color Palette
    make_gradient( // ... to a gradient made from
      CRGB::Green, // ... Green to
      CRGB::Black // .... Black.
    )
  );

  pix.set_color_animation(ANIMATION_STATIC);
  // An unmoving (static) Color Animation is required to show Color Palettes
}

void loop() {
  // Enable gamma correction, show gradient
  pix.set_gamma_correction(true);
  pix.clear();
  pix.print("[:PASS:]---");
  pix.show();
  delay(1000);

  // Disable gamma correction, show gradient
  pix.set_gamma_correction(false);
  pix.clear();
  pix.print("[:FAIL:]---");
  pix.show();
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