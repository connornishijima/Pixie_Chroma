/*!
 * @file Pixie_Chroma.h
 *
 * Designed specifically to work with Pixie Chroma:
 * ----> https://connornishijima.github.io/PixieChroma
 *
 * Last Updated by Connor Nishijima on 10/21/21
 */

/*

     ██  ██  ██  ██          ██  ██  ██      ██              ██      ██  ██  ██      ██  ██  ██  ██  ██
  
     ██              ██          ██          ██              ██          ██          ██  
  
     ██              ██          ██              ██      ██              ██          ██  
  
     ██  ██  ██  ██              ██                 ██                   ██          ██  ██  ██  ██  ██
   
     ██                          ██             ██      ██               ██          ██  
  
     ██                          ██          ██              ██          ██          ██  
  
     ██                      ██  ██  ██      ██              ██      ██  ██  ██      ██  ██  ██  ██  ██
  
                              ██████ ██   ██ ██████   ██████  ███    ███  █████  
                             ██      ██   ██ ██   ██ ██    ██ ████  ████ ██   ██ 
                             ██      ███████ ██████  ██    ██ ██ ████ ██ ███████ 
                             ██      ██   ██ ██   ██ ██    ██ ██  ██  ██ ██   ██ 
                              ██████ ██   ██ ██   ██  ██████  ██      ██ ██   ██
   
                                                by @LixieLabs

    ----------------------------------------------------------------------------------------------------

    Welcome to the source code of the Pixie Chroma library!

    "PixieChroma.h" is the main file, which loads all others, including
    the pixie_chroma_internal.h/.cpp that contain the PixieChroma class definitions.

    ----------------------------------------------------------------------------------------------------
*/

#include "Arduino.h" // Needed for things like uint8_t typedefs

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
	// FastLED has issues with the ESP8266, especially
	// when used with networking, so we fix that here.
	#define FASTLED_ESP8266_RAW_PIN_ORDER
	//#define FASTLED_ALLOW_INTERRUPTS 0
	//#define FASTLED_INTERRUPT_RETRY_COUNT 0
#endif

#define FASTLED_INTERNAL // As in: INTERNALize your thoughts about how we bang bits when you go to compile, FastLED.
#include "FastLED.h"     // Apart from some issues, it's my tool of choice for WS2812B/compatibles because it's actually amazingly useful

#include "utility/pixie_palettes.h" // ----- Color Palettes
#include "utility/pixie_font.h" // --------- ASCII font
#include "utility/pixie_icons.h" // -------- Bitmap icon pack
#include "utility/pixie_animations.h" // --- Preset animation routines
#include "pixie_chroma_internal.h" // ------ Main library code
