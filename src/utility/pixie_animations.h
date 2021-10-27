/*!
 * @file pixie_animations.h
 *
 * Designed specifically to work with Pixie Chroma:
 * ----> https://connornishijima.github.io/PixieChroma
 *
 * Last Updated by Connor Nishijima on 10/21/21
 */

#ifndef pixie_animations_h
#define pixie_animations_h

#include "../Pixie_Chroma.h"

/**************************************************************************/
/*!
    @brief  It does nothing, but it does nothing REALLY WELL! You can enable
            this empty function with pix.set_animation(ANIMATION_NULL) to
            fully manually control LEDs when you want using pix.show().
*/
/**************************************************************************/
void ANIMATION_NULL(); // Prototype definition needed so _pixie_chroma.cpp can reach these functions as well as the sketch

/**************************************************************************/
/*!
    @brief  Shows the current color palette without animation.
*/
/**************************************************************************/
void ANIMATION_SOLID();

/**************************************************************************/
/*!
    @brief  Shows the current color palette, while constantly shifting it
            to the left.
*/
/**************************************************************************/
void ANIMATION_PALETTE_SHIFT_LEFT();

/**************************************************************************/
/*!
    @brief  Shows the current color palette, while constantly shifting it
            to the right.
*/
/**************************************************************************/
void ANIMATION_PALETTE_SHIFT_RIGHT();

void ANIMATION_GLITTER();

void ANIMATION_PENDULUM();
void ANIMATION_PENDULUM_WIDE();

void _PALETTE_SHIFT(int8_t amount);
void _PENDULUM(float iter, float width);


/**************************************************************************/
/*!
    @brief  Converts 2 CRGB colors to a gradient, and creates a color
            palette from that gradient.
*/
/**************************************************************************/
CRGBPalette16 make_gradient(CRGB col1, CRGB col2);


/**************************************************************************/
/*!
    @brief  Converts 3 CRGB colors to a gradient, and creates a color
            palette from that gradient.
*/
/**************************************************************************/
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3);


/**************************************************************************/
/*!
    @brief  Converts 4 CRGB colors to a gradient, and creates a color
            palette from that gradient.
*/
/**************************************************************************/
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4);


/**************************************************************************/
/*!
    @brief  Converts 5 CRGB colors to a gradient, and creates a color
            palette from that gradient.
*/
/**************************************************************************/
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5);


/**************************************************************************/
/*!
    @brief  Converts 6 CRGB colors to a gradient, and creates a color
            palette from that gradient.
*/
/**************************************************************************/
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6);


/**************************************************************************/
/*!
    @brief  Converts 7 CRGB colors to a gradient, and creates a color
            palette from that gradient.
*/
/**************************************************************************/
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7);


/**************************************************************************/
/*!
    @brief  Converts 8 CRGB colors to a gradient, and creates a color
            palette from that gradient.
*/
/**************************************************************************/
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7, CRGB col8);

#endif
