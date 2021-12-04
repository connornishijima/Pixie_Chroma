/*----------------------------------------------------------------------------

  Pixie Chroma | Serial_Monitor.ino
  by Connor Nishijima Dec. 2021
  -------------------------------------

  This sketch is for showing live incoming Serial data on Pixies, especially
  useful on multi-line displays!
  
----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define DATA_PIN   12 // GPIO to use for Pixie Chroma data line
#define PIXIES_X   6  // Total amount and arrangement
#define PIXIES_Y   2  // of Pixie PCBs = 6 x 2
                      // See "WIRING" below!

char in_string[255];     // Temporary storage for incoming data
uint8_t char_index = 0; // Character index for incoming data

void setup() {
  pix.begin_quad( 3, PIXIES_X, PIXIES_Y );
  // Initializes the displays, and sets things
  // like the default power budget for you.

  Serial.begin(115200); // ...... Opens a UART connection at 115200 baud
  pix.color( CRGB::Cyan ); // ... Sets the global color to *CYAN*
}

void loop() {
  if(Serial.available() > 0){ // Data incoming?
    char c = Serial.read(); // Read one character
    if(c != '\n'){ // If it's not a "newline", add the new character to the temporary string
      in_string[char_index] = c;
      char_index++;
      if(char_index == 255){
        char_index = 255;
      }
    }
    else{ // If it IS a newline, print the temporary string built so far to the Pixies
      in_string[char_index] = 0;
      pix.shift_mask_y(-11); // Shift old data up
      pix.set_cursor(0,PIXIES_Y-1); // Set cursor to bottom row
      pix.print(in_string);
      pix.show(); // Show new data

      // Reset temporary storage
      memset(in_string,0,255);
      char_index = 0;
    }
  }
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