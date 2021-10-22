/*!
 * @file _pixie_animations.h
 *
 * Designed specifically to work with Pixie Chroma:
 * ----> https://connornishijima.github.io/PixieChroma
 *
 * Last Updated by Connor Nishijima on 10/21/21
 */

#ifndef pixie_animations_h
#define pixie_animations_h

#include "../PixieChroma.h"

void ANIMATION_NULL(); // Prototype definition needed so _pixie_chroma.cpp can reach these functions as well as the sketch
void ANIMATION_SOLID();

void ANIMATION_PALETTE_SHIFT_LEFT();
void ANIMATION_PALETTE_SHIFT_RIGHT();

void ANIMATION_GLITTER();

void ANIMATION_PENDULUM();
void ANIMATION_PENDULUM_WIDE();

void _PALETTE_SHIFT(int8_t amount);
void _PENDULUM(float iter, float width);

CRGBPalette16 make_gradient(CRGB col1, CRGB col2);
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3);
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4);
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5);
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6);
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7);
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7, CRGB col8);

#endif
