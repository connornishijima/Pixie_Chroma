/*----------------------------------------------------------------------------

  Pixie Chroma | 06_Shortcode_Library.ino
  by Connor Nishijima Feb. 2022
  ----------------------------------

  This sketch demonstrates the use of "Shortcodes".

  Shortcodes are a super simple way to show icons beyond the alphanumeric
  ASCII set and easily create animations! We have an extensive library of
  230+ built-in icons that are accessible by name within other strings.
  Whether you want global currency symbols, weather states, schematic
  symbols, diacritics (àãåâä), or various mathematical typography such as
  pi, we probably have you covered. And, if we don't, you can make your
  own with the magical Shortcode Editor:

  https://connornishijima.github.io/Pixie_Chroma/?section=shortcodes

  Shortcodes are defined with an opening and closing set of special characters:

    [:NAME_HERE:]

  For example, pix.print( "[:CLOCK:]" ) will print a custom icon of a clock.
  Inline custom shortcodes are also available, defined with a "#" at the
  start of the code like so:

    [:#08043E0408:] // Custom up-arrow icon, generated
                       with the Shortcode Editor.

  Shortcodes can even exist inside other strings, like so:

    pix.print( "We [:HEART:] you!" ); // Prints a heart icon

  In this example, we use inline shortcodes to show a "spinner" animation
  next to text in the same print() call.

----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define DATA_PIN  5 // GPIO to use for Pixie Chroma data line
#define PIXIES_X  2  // Total amount and arrangement
#define PIXIES_Y  1  // of Pixie PCBs = 2 x 1 
                     //
                     // See "WIRING" below!

void setup() {
  pix.begin( DATA_PIN, PIXIES_X, PIXIES_Y );
  // Initializes the displays, and sets things
  // like the default power budget for you. 

  pix.color( CRGB(90,0,255) ); // ... Set the entire display to purple
}

void loop() {
  show_frame( "[:SPINNER_1:] HI" ); // See "show_frame()" function below for usage
  show_frame( "[:SPINNER_2:] HI" );
  show_frame( "[:SPINNER_3:] HI" );
  show_frame( "[:SPINNER_4:] HI" );
  show_frame( "[:SPINNER_5:] HI" );
  show_frame( "[:SPINNER_6:] HI" );
  show_frame( "[:SPINNER_7:] HI" );
  show_frame( "[:SPINNER_8:] HI" );
  show_frame( "[:SPINNER_9:] HI" );
  show_frame("[:SPINNER_10:] HI" );

  // REPEAT
}

void show_frame(char* message){
  pix.clear(); // .......... Clear the display buffer
  pix.print(message); // ... Print a text or shortcodes to the display, and
  pix.show(); // ........... send the updated image to the Pixies.
  delay(50); // ............ Wait between frames
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
