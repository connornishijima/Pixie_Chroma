/*

     ██  ██  ██  ██        ██  ██  ██  	  ██              ██	    ██  ██  ██  	██  ██  ██  ██  ██	
  
     ██              ██        ██     	  ██              ██	        ██      	██  	
  
     ██              ██        ██     	      ██      ██    	        ██      	██  	
  
     ██  ██  ██  ██  	       ██     	          ██        	        ██      	██  ██  ██  ██  ██	
  
     ██              	       ██     	      ██      ██    	        ██      	██  	
  
     ██              	       ██      	  ██              ██	        ██      	██  
  
     ██              	   ██  ██  ██  	  ██              ██	    ██  ██  ██    	██  ██  ██  ██  ██	
  
                       ██████ ██   ██ ██████   ██████  ███    ███  █████  
                      ██      ██   ██ ██   ██ ██    ██ ████  ████ ██   ██ 
                      ██      ███████ ██████  ██    ██ ██ ████ ██ ███████ 
                      ██      ██   ██ ██   ██ ██    ██ ██  ██  ██ ██   ██ 
                       ██████ ██   ██ ██   ██  ██████  ██      ██ ██   ██
					   
					                     by @LixieLabs

	--------------------------------------------------------------------------------------------------

	Welcome to the source code of the Pixie Chroma library!

	"PixieChroma.h" is the main file, which loads all others, including
	the _pixie_chroma.h/.cpp that contain the PixieChroma class definitions.

	--------------------------------------------------------------------------------------------------
*/

#include "Arduino.h" // Needed for things like uint8_t typedefs

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
	// FastLED has issues with the ESP8266, especially
	// when used with networking, so we fix that here.
	#include <Ticker.h>	// ESP ONLY
	#define FASTLED_ESP8266_RAW_PIN_ORDER
	//#define FASTLED_ALLOW_INTERRUPTS 		0
	//#define FASTLED_INTERRUPT_RETRY_COUNT	0
#endif

#define FASTLED_INTERNAL // As in: INTERNALize your thoughts about how we bang bits when you go to compile, FastLED.
#include "FastLED.h"     // Apart from some issues, it's my tool of choice for WS2812B/compatibles

#include "utility/_pixie_palettes.h" // ----- Color Palettes
#include "utility/_pixie_font.h" // --------- ASCII font
#include "utility/_pixie_icons.h" // -------- Bitmap icon pack
#include "utility/_pixie_animations.h" // --- Preset animation routines
#include "_pixie_chroma.h" // --------------- Main library code