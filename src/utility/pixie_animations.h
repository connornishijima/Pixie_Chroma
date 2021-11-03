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


/*! ############################################################################
    @brief
    It does nothing, but it does nothing REALLY WELL! You can enable this empty
    function with pix.set_animation(ANIMATION_NULL) to fully manually control
    LEDs when you want using pix.show().
*///............................................................................
void ANIMATION_NULL(float delta); // Prototype definition needed so pixie_chroma_internal.cpp can reach these functions as well as the sketch


/*! ############################################################################
    @brief
    Shows the current color palette without animation.
*///............................................................................
void ANIMATION_STATIC(float delta);


/*! ############################################################################
    @brief
    Shows the current color palette, while constantly shifting it to the left.
*///............................................................................
void ANIMATION_PALETTE_SHIFT_LEFT(float delta);


/*! ############################################################################
    @brief
    Shows the current color palette, while constantly shifting it to the right.
*///............................................................................
void ANIMATION_PALETTE_SHIFT_RIGHT(float delta);


/*! ############################################################################
    @brief
    Shows the current color palette with a sparkling effect.
*///............................................................................
void ANIMATION_GLITTER(float delta);


/*! ############################################################################
    @brief
    Sways the current color palette left and right with a sine function at 1Hz
    intervals
*///............................................................................
void ANIMATION_PENDULUM(float delta);


/*! ############################################################################
    @brief
    Sways the current color palette left and right with a sine function at 1Hz
    intervals. Wider travel than ANIMATION_PENDULUM
*///............................................................................
void ANIMATION_PENDULUM_WIDE(float delta);


/*! ############################################################################
    @brief
    Internal animation, shifts the color palette a fixed amount on each run.
*///............................................................................
void ANIMATION_PALETTE_SHIFT(int8_t amount, float delta);


/*! ############################################################################
    @brief
    Internal animation that sways the current color palette left and right with
    a sine function at 1Hz intervals. (Custom width)
*///............................................................................
void _PENDULUM(float iter, float width);


/*! @brief  Converts a set of CRGB colors to a gradient, and creates a color palette from that gradient. */
CRGBPalette16 make_gradient(CRGB col1, CRGB col2);
/*! @brief  Converts a set of CRGB colors to a gradient, and creates a color palette from that gradient. */
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3);
/*! @brief  Converts a set of CRGB colors to a gradient, and creates a color palette from that gradient. */
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4);
/*! @brief  Converts a set of CRGB colors to a gradient, and creates a color palette from that gradient. */
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5);
/*! @brief  Converts a set of CRGB colors to a gradient, and creates a color palette from that gradient. */
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6);
/*! @brief  Converts a set of CRGB colors to a gradient, and creates a color palette from that gradient. */
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7);
/*! @brief  Converts a set of CRGB colors to a gradient, and creates a color palette from that gradient. */
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7, CRGB col8);

#endif
