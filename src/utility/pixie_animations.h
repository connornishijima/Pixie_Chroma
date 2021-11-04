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
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_NULL(PixieChroma* _p, float delta); // Prototype definition needed so pixie_chroma_internal.cpp can reach these functions as well as the sketch


/*! ############################################################################
    @brief
    Shows the current color palette without animation.
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_STATIC(PixieChroma* _p, float delta);


/*! ############################################################################
    @brief
    Shows the current color palette, while constantly shifting it to the left.
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_PALETTE_SHIFT_LEFT(PixieChroma* _p, float delta);


/*! ############################################################################
    @brief
    Shows the current color palette, while constantly shifting it to the right.
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_PALETTE_SHIFT_RIGHT(PixieChroma* _p, float delta);


/*! ############################################################################
    @brief
    Shows the current color palette with a sparkling effect.
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_GLITTER(PixieChroma* _p, float delta);


/*! ############################################################################
    @brief
    Sways the current color palette left and right with a sine function at 1Hz
    intervals
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_PENDULUM(PixieChroma* _p, float delta);


/*! ############################################################################
    @brief
    Sways the current color palette left and right with a sine function at 1Hz
    intervals. Wider travel than ANIMATION_PENDULUM
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_PENDULUM_WIDE(PixieChroma* _p, float delta);


/*! ############################################################################
    @brief
    Internal animation, shifts the color palette a fixed amount on each run.
    @param  amount Amount to shift the color palette (in 1/256ths) each frame
    @param  delta  Used to regulate animation playback consistency if
                   performance drops
*///............................................................................
void ANIMATION_PALETTE_SHIFT(PixieChroma* _p, int8_t amount, float delta);


/*! ############################################################################
    @brief
    Internal animation that sways the current color palette left and right with
    a sine function at 1Hz intervals. (Custom width)
    @param  center_position  Offset of the color palette left or right
    @param  sway_width       Offset multiplier
*///............................................................................
void _PENDULUM(PixieChroma* _p, float center_position, float sway_width);

    
/*! ############################################################################
    @brief
    Converts a set of CRGB colors to a gradient, and creates a color palette
    from that gradient.
    @param   col1  First color
    @param   col2  Second color
    @return  A CRGBPalette16 object for use with set_palette()
*///............................................................................
CRGBPalette16 make_gradient(CRGB col1, CRGB col2);

    
/*! ############################################################################
    @brief
    Converts a set of CRGB colors to a gradient, and creates a color palette
    from that gradient.
    @param   col1  First color
    @param   col2  Second color
    @param   col3  Third color
    @return  A CRGBPalette16 object for use with set_palette()
*///............................................................................
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3);


/*! ############################################################################
    @brief
    Converts a set of CRGB colors to a gradient, and creates a color palette
    from that gradient.
    @param   col1  First color
    @param   col2  Second color
    @param   col3  Third color
    @param   col4  Fourth color
    @return  A CRGBPalette16 object for use with set_palette()
*///............................................................................
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4);

    
/*! ############################################################################
    @brief
    Converts a set of CRGB colors to a gradient, and creates a color palette
    from that gradient.
    @param   col1  First color
    @param   col2  Second color
    @param   col3  Third color
    @param   col4  Fourth color
    @param   col5  Fifth color
    @return  A CRGBPalette16 object for use with set_palette()
*///............................................................................
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5);


/*! ############################################################################
    @brief
    Converts a set of CRGB colors to a gradient, and creates a color palette
    from that gradient.
    @param   col1  First color
    @param   col2  Second color
    @param   col3  Third color
    @param   col4  Fourth color
    @param   col5  Fifth color
    @param   col6  Sixth color
    @return  A CRGBPalette16 object for use with set_palette()
*///............................................................................
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6);


/*! ############################################################################
    @brief
    Converts a set of CRGB colors to a gradient, and creates a color palette
    from that gradient.
    @param   col1  First color
    @param   col2  Second color
    @param   col3  Third color
    @param   col4  Fourth color
    @param   col5  Fifth color
    @param   col6  Sixth color
    @param   col7  Seventh color
    @return  A CRGBPalette16 object for use with set_palette()
*///............................................................................
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7);


/*! ############################################################################
    @brief
    Converts a set of CRGB colors to a gradient, and creates a color palette
    from that gradient.
    @param   col1  First color
    @param   col2  Second color
    @param   col3  Third color
    @param   col4  Fourth color
    @param   col5  Fifth color
    @param   col6  Sixth color
    @param   col7  Seventh color
    @param   col8  Eighth color
    @return  A CRGBPalette16 object for use with set_palette()
*///............................................................................
CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7, CRGB col8);

#endif
