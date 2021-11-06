<br>
<img src="extras/img/logo.png">
<p align="center">
  <b>Arduino library and documentation for Pixie Chroma displays!</b><br>
  &nbsp;&nbsp;· · ·&nbsp;&nbsp;
  <a href="https://connornishijima.github.io/Pixie_Chroma/?section=docs"><b>LIBRARY DOCS</b></a>
  &nbsp;&nbsp;· · ·&nbsp;&nbsp;
  <a href="https://connornishijima.github.io/Pixie_Chroma/?section=datasheet"><b>DATASHEET</b></a>
  &nbsp;&nbsp;· · ·&nbsp;&nbsp;
  <a href="https://connornishijima.github.io/Pixie_Chroma/?section=tutorials"><b>TUTORIALS</b></a>
  &nbsp;&nbsp;· · ·&nbsp;&nbsp;
  <a href="extras/OSHW/PCB"><b>OSHW</b></a>
  &nbsp;&nbsp;· · ·&nbsp;&nbsp;
</p>
<br>
<p align="center">
  <img src="https://github.com/connornishijima/Pixie_Chroma/actions/workflows/arduino_lint.yml/badge.svg">
  <img src="https://github.com/connornishijima/Pixie_Chroma/actions/workflows/arduino_build.yml/badge.svg">
  <img src="https://github.com/connornishijima/Pixie_Chroma/actions/workflows/docs_and_reports.yml/badge.svg">
  <a href="https://www.ardu-badge.com/Pixie_Chroma"><img src="https://www.ardu-badge.com/badge/Pixie_Chroma.svg"></a>
</p>

-------------------------------------------------------------------------------

**PIXIE CHROMA** is a dual-5x7 character display for Arduino, that can be easily chained to create easy-to-use displays as long or tall as you'd like! Featuring 70 addressable RGB LEDs, Pixie Chroma can be controlled with as little as a single GPIO!

---------------------------------------------------------------------------------

### **NOTE: *This repository/library are still under construction,***

- ***Make sure to [follow our Twitter](https://twitter.com/lixielabs) for official releases!***

---------------------------------------------------------------------------------

![PIXIE CHROMA PCB](extras/img/PCB_SINGLE.png)

## Table of Contents

- [Intro](#the-coolest-character-display-for-arduino)
- [Code Demo](#code-demo)

# The Coolest Character Display for Arduino

- Dual 5x7 RGB LED matrices
- 3.7V to 5.5V supply
- Fast bitmap control
- 8-bit global dimming
- 27.5mm * 16.5mm matrix size (10.16 ppi)
- 30mm * 24mm package

# Code Demo

Here's a quick peek at how easy it is to use a Pixie display:

```cpp
#include "Pixie_Chroma.h" // Include library
PixieChroma pix;
#define PIXIES_X  6  // Total amount and         x x x x x x
#define PIXIES_Y  2  // arrangement of Pixies =  x x x x x x

void setup() {
  pix.begin( 13, PIXIES_X, PIXIES_Y ); // ... Use Pin 13
  pix.color( CRGB::Blue ); // ............... Set color to blue
}

void loop() {
  pix.clear(); // ..................... Clear display
  pix.println( "Hello World!" ); // ... Write text on first row
  pix.print( millis() ); // ........... Write the value of millis() on the second row
  pix.show(); // ...................... Show changes
}
```
		
In just 16 lines, you're in control of over 800 LEDs to show any text you'd like! 
	
Pixie Chroma also makes it extremely easy to control advanced animation in the background while other code runs! For example:

```cpp
#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class instance

#define PIXIES_PER_PIN  3  // ... Pixies per data line

#define PIXIES_X  6  // ......... Total amount and         x x x x x x
#define PIXIES_Y  2  // ......... arrangement of Pixies =  x x x x x x

void setup() {
  pix.begin_quad( PIXIES_PER_PIN, PIXIES_X, PIXIES_Y ); // Initialize Pixies to use 4 GPIO in
                                                        // parallel, with three Pixies on each line

  pix.set_max_power( 5, 500 ); // ............................ Set power budget to 5V, 500mA

  // Set the color palette to use for showing our text
  pix.set_palette(
    make_gradient( // ........... For our palette, we'll generate a gradient from:
      CRGB(255, 0,   0  ), // ... RED,
      CRGB(0,   255, 0  ), // ... GREEN,
      CRGB(255, 0,   0  )  // ... and RED.
    )
  );

  // Set the animation preset to "PALETTE SHIFT RIGHT",
  // which will cause our gradient to scroll left-to-right
  pix.set_animation( ANIMATION_PALETTE_SHIFT_RIGHT );
  
  // Run animation at half-speed
  pix.set_animation_speed( 0.5 );

  // Sets the library into AUTOMATIC mode, which keeps 
  // the animation running smoothly in the background
  // while the microcontroller runs other functions                                  
  pix.set_update_mode( AUTOMATIC ); 
}

uint32_t counter = 0; // This is a number to show on the display

void loop() {
  pix.clear(); // ............ Clears the display
  pix.print( counter ); // ... Prints the value of "counter" to the display

  delay(500); // ............. Delay. During this time, animation will continue
  	      //               smoothly scrolling our gradient defined in setup()

  counter++; // .............. Increment counter
}
```

As you can see, Pixie Chroma is **as easy or advanced as you need!** Luckily, you don't need to dive into documentation to get started - the included examples (`File -> Examples -> Pixie_Chroma`) are an easy template to modify for your own projects!

![HELLO WORLD](extras/img/hello_world.png)
