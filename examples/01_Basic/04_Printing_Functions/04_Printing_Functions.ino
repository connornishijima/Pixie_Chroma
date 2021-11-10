/*----------------------------------------------------------------------------

  Pixie Chroma | 04_Printing_Functions.ino
  by Connor Nishijima Nov. 2021
  ----------------------------------------

  This sketch demonstrates the various printing functions available to you in
  the Pixie Chroma library! You can use any of the following types with
  pix.print() or pix.println():

  - char* (char array / "string")
  - uint8_t
  - uint16_t
  - uint32_t
  - int8_t
  - int16_t
  - int32_t
  - float
  - double
  - Icon (see 02_Advanced/14_Icon_Library)

  This print() function is how you'll write text to the Pixie displays!

  There are two basic printing functions that you'll use the most:

  - print() will add your input at the current cursor position, which is 
    automatically tracked and updated with each call to print().

  - println() is functionally identical, but will always append a line-return
    after every input, which is useful for multi-line displays.

  You can also include '\n' (newline) characters in strings you're printing,
  like so:

    pix.print("LINE 1\nLINE 2")

              =

    pix.println("LINE 1");
    pix.print("LINE 2");

  Using clear() at any time will reset the cursor position to your
  top-left display, or you can use pix.set_cursor(0,0);

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
}

void loop() {
  // ### UNSIGNED INTEGERS (Positive values) ##########################
  
  // uint8_t ----------------------------------------------------------
  uint8_t print_value_a = 123;
  pix.clear(); // .................. Clear the display buffer,
  pix.color( CRGB::Red ); // ....... set color to red,
  pix.print( print_value_a ); // ... print a uint8_t value and
  pix.show(); // ................... send the updated image to the Pixies.
  delay(1000);

  // uint16_t ---------------------------------------------------------
  uint16_t print_value_b = 4567;
  pix.clear(); // .................. Clear the display buffer,
  pix.color( CRGB::Green ); // ..... set color to green,
  pix.print( print_value_b ); // ... print a uint16_t value and
  pix.show(); // ................... send the updated image to the Pixies.
  delay(1000);

  // uint32_t ---------------------------------------------------------
  uint32_t print_value_c = 89012;
  pix.clear(); // .................. Clear the display buffer,
  pix.color( CRGB::Blue ); // ...... set color to blue,
  pix.print( print_value_c ); // ... print a uint32_t value and
  pix.show(); // ................... send the updated image to the Pixies.
  delay(1000);


  // ### SIGNED INTEGERS (Positive/Negative values) ##################

  // int8_t ----------------------------------------------------------
  int8_t print_value_d = -34;
  pix.clear(); // .................. Clear the display buffer,
  pix.color( CRGB::Red ); // ....... set color to red,
  pix.print( print_value_d ); // ... print a int8_t value and
  pix.show(); // ................... send the updated image to the Pixies.
  delay(1000);

  // int16_t ---------------------------------------------------------
  int16_t print_value_e = -5678;
  pix.clear(); // .................. Clear the display buffer,
  pix.color( CRGB::Green ); // ..... set color to green,
  pix.print( print_value_e ); // ... print a int16_t value and
  pix.show(); // ................... send the updated image to the Pixies.
  delay(1000);

  // int32_t ---------------------------------------------------------
  int32_t print_value_f = -901234;
  pix.clear(); // .................. Clear the display buffer,
  pix.color( CRGB::Blue ); // ...... set color to blue,
  pix.print( print_value_f ); // ... print a int32_t value and
  pix.show(); // ................... send the updated image to the Pixies.
  delay(1000);


  // ### Floating Point (Fractional values) ##########################

  // float -----------------------------------------------------------
  float print_value_g = 5.678;
  pix.clear(); // ................. Clear the display buffer,
  pix.color( CRGB::Yellow ); // ... set color to yellow,
  pix.print(     // ............... print a
    print_value_g, // ............. single precision floating point value
    2            // ............... to two decimal place(s) of precision and
  ); 
  pix.show(); // .................. send the updated image to the Pixies.
  delay(1000);

  // double -----------------------------------------------------------
  double print_value_h = -9.012;
  pix.clear(); // ................. Clear the display buffer,
  pix.color( CRGB::Purple ); // ... set color to purple,
  pix.print(     // ............... print a
    print_value_h, // ............. double precision floating point value
    1            // ............... to one decimal place(s) of precision and
  ); 
  pix.show(); // .................. send the updated image to the Pixies.
  delay(1000);


  // ### Char Array ##################################################

  // char[] (Array) --------------------------------------------------
  char print_value_i[5] = {'T','e','s','t','\0'}; // "Null terminator" needed!
  
  pix.clear(); // .................. Clear the display buffer,
  pix.color( CRGB::Magenta ); // ... set color to magenta,
  pix.print(print_value_i); //...... print a char[] array, and
  pix.show(); // ................... send the updated image to the Pixies.
  delay(1000);

  // char* (Pointer) -------------------------------------------------
  char* print_value_j = "HI:)";
  pix.clear(); // ................. Clear the display buffer,
  pix.color( CRGB::Orange ); // ... set color to orange,
  pix.print(print_value_j); //..... print a char* pointer, and
  pix.show(); // .................. send the updated image to the Pixies.
  delay(1000);


  // ### Icons #######################################################

  pix.clear(); // ............... Clear the display buffer,
  pix.color( CRGB::Cyan ); // ... set color to cyan,
  pix.print(ICON_HEART); //...... print ICON_HEART, 
  pix.print(ICON_EXPORT); //..... print ICON_EXPORT,
  pix.print(ICON_BITCOIN); //.... print ICON_BITCOIN,
  pix.print(ICON_A_UMLAUT); //... print ICON_A_UMLAUT, and
  pix.show(); // ................ send the updated image to the Pixies.
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