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

    "Pixie_Chroma.h" is the main file, which loads all others, including
    the pixie_chroma_internal.h/.cpp that contain the Pixie_Chroma class definitions.

    ----------------------------------------------------------------------------------------------------
*/

#include "Arduino.h" // Needed for things like uint8_t typedefs

#if defined(__MK20DX128__) || defined(__MK20DX256__)
	#define ARDUINO_ARCH_TEENSY_3_X	1
#endif

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
	#define FASTLED_ESP8266_RAW_PIN_ORDER
	#include "Ticker.h"  // Ticker for optional automated show() calls
#elif defined(ARDUINO_ARCH_TEENSY_3_X)
	#include <MsTimer2.h> // MsTimer2 for optional automated show() calls
#else
	#error "This library currently only supports ESP8266, ESP32, or TEENSY 3.X controllers."
#endif

#if defined(ARDUINO_ARCH_ESP32)
	#define FASTLED_ESP32_I2S true
	#define FASTLED_RMT_MAX_CHANNELS 4
	#define FASTLED_ESP32_FLASH_LOCK 1
#endif

/** @brief Used to quiet unavoidable FastLED warnings about bit banging. */
#define FASTLED_INTERNAL // As in: INTERNALize your thoughts about how we bang bits when you go to compile, FastLED.
#include "FastLED.h"     // Apart from some issues, it's my tool of choice for WS2812B/compatibles because it's actually amazingly useful

#include "utility/pixie_palettes.h" // ----- Color Palettes
#include "utility/pixie_font.h" // --------- ASCII font
#include "utility/pixie_shortcodes.h" // --- Bitmap Icon pack
#include "utility/pixie_animations.h" // --- Preset animation routines
#include "pixie_chroma_internal.h" // ------ Main library code

/** @brief Developer use - unit testing defaults. */
#define UNIT_TEST_PIXIES_PER_PIN 3
/** @brief Developer use - unit testing defaults. */
#define UNIT_TEST_PIXIES_X       6
/** @brief Developer use - unit testing defaults. */
#define UNIT_TEST_PIXIES_Y       2
