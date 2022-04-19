/*----------------------------------------------------------------------------

  Pixie Chroma | 10_Update_Modes.ino
  by Connor Nishijima Nov. 2021
  ----------------------------------

  This sketch demonstrates the (optional) use of the AUTOMATIC update mode.

    pix.set_update_mode( MODE, FPS = 60);

  "MODE" can be MANUAL or AUTOMATIC. (Default MANUAL)
  
  MANUAL MODE:
    The Pixies will only show updates if and when you call show(). If you are
    not calling show() often enough, Animations can look choppy. This means
    that delay() is basically off-limits if you're using Animations, as your
    Pixies will not update during this time. However, this offers the highest
    amount of control for when LEDs change, and frame rate is only limited by
    the speed of your code/controller.

  AUTOMATIC MODE:
    The Pixie will automatically call show() at [FPS] using interrupts. This
    will keep Animations running smoothly, but can interrupt other functions.
    (In most cases this is fine.) To prevent Mask updates from showing if the
    a frame is sent before text is finished being constructed, you can use
    pix.hold() before any clear()/print() calls, and pix.free() once you are
    ready for the text to be shown on the next frame.

  ----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define DATA_PIN  12 // GPIO to use for Pixie Chroma data line
#define PIXIES_X  2  // Total amount and arrangement
#define PIXIES_Y  1  // of Pixie PCBs = 2 x 1
                     //
                     // See "WIRING" below!

// Frame rate to target
const int FPS = 30;

void setup() {
  pix.begin( DATA_PIN, PIXIES_X, PIXIES_Y );
  // Initializes the displays, and sets things
  // like the default power budget for you.

  pix.clear(); // ....... Clears the display buffer, and
  pix.set_palette(RAINBOW);

  pix.set_color_animation_speed(2.0); // 200% Speed!
  pix.set_color_animation(ANIMATION_PALETTE_SHIFT_LEFT); // ... Set animation and
  pix.set_update_mode(AUTOMATIC, FPS); // ..................... and set the frame
                                       // ..................... rate target to 30FPS
}

void loop() {
  static int count = 100;
  
  pix.hold(); // hold() prevents Mask updates from showing if the frame is
              // sent before text is finished being constructed. Animation
              // and Color Map updates will continue as normal. If running
              // in AUTOMATIC mode like this, always use hold() before
              // any chains of clear() / print() calls are needed.
              
  pix.clear();            // 
  pix.print("[:SMILE:]"); // Build a frame to show
  pix.print(count++);     // 
  
  pix.free(); // free() releases library to show the updated mask
              // on the next frame render

  delay(1000); // During this delay, animation will continue as normal, since
               // set_update_mode(AUTOMATIC) was used. Your loop() will be
               // interrupted [FPS] times per second to keep the animation
               // up to date.

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