/*!
 * @file pixie_chroma_internal.cpp
 *
 * Designed specifically to work with Pixie Chroma:
 * ----> https://connornishijima.github.io/PixieChroma
 *
 * Last Updated by Connor Nishijima on 10/21/21
 */

#include "Pixie_Chroma.h" 
#include "utility/pixie_utility.h"

// TODO: Call pix.show() from Ticker without need for wrapper function 
// I'm currently unable to figure out how to feed a class function (non-static) like `pix::show()` to `Ticker::attach_ms()`.
// ```
// void show_container(){
//   extern PixieChroma pix;
//   pix.show();
// }
// ```

/*! ############################################################################
    @brief
    Used for auto_update() so that Ticker can access this specific Pixie Chroma
    instance. Slightly hacky with the `extern`.
*///............................................................................
void show_container(){
    extern PixieChroma pix;
    pix.show();
}


// ---------------------------------------------------------------------------------------------------------|
// -- PUBLIC CLASS FUNCTIONS -------------------------------------------------------------------------------|
// ---------------------------------------------------------------------------------------------------------|


/*! ############################################################################
    @brief
    Used to initialize the PixieChroma library.
    
    @details
    Example usage before `setup()` would be:
    
        #include "Pixie_Chroma.h"
        PixieChroma pix;
    
    NOTE: Due to current limitations with the library, your class
    instance MUST be named `pix`. Mutiple instances are not yet
    possible. Because each of these functions are contained in the
    PixieChroma class object, you'll use them like this:
    
        pix.print( "Hello!" );
*///............................................................................
PixieChroma::PixieChroma(){}


/*! ############################################################################
    @brief
    Initializes the display buffer, populates the XY coordinate table, defaults
    the display colors to green, loads the default CRGBPalette, initializes
    FastLED, and sets the default power budget.
             
    @details
    Pixie Chroma allows for multi-row displays, which are wired in reading
    order (left to right, top to bottom) and their shape is defined here. For
    example, a 16-Pixie display with two rows of eight:
              
        data_pin
           |
        +--+-+   +----+   +----+   +----+   +----+   +----+   +----+   +----+
        |  1 |-->|  2 |-->|  3 |-->|  4 |-->|  5 |-->|  6 |-->|  7 |-->|  8 | 
        +----+   +----+   +----+   +----+   +----+   +----+   +----+   +--+-+
                                                                          |
           +--------------------------------------------------------------+
           |
        +--+-+   +----+   +----+   +----+   +----+   +----+   +----+   +----+
        |  9 |-->| 10 |-->| 11 |-->| 12 |-->| 13 |-->| 14 |-->| 15 |-->| 16 | 
        +----+   +----+   +----+   +----+   +----+   +----+   +----+   +----+

    The corresponding setup for this display layout would be:
    
        #include "Pixie_Chroma.h"
        PixieChroma pix;
        
        #define DATA_PIN 5
        #define PIXIES_X 8
        #define PIXIES_Y 2
        
        void setup() {
            pix.begin( DATA_PIN, PIXIES_X, PIXIES_Y );
        }
    
    For faster performance on large displays, see begin_quad().
    
    @param  data_pin GPIO pin to use for FastLED output
    @param  pixies_x Number of Pixie PCBs in the X axis of your display
    @param  pixies_y Number of Pixie PCBs in the Y axis of your display
*///............................................................................
void PixieChroma::begin( const uint8_t data_pin, uint8_t pixies_x, uint8_t pixies_y ){
    pixie_pin = data_pin;

    chars_x = pixies_x * 2; // Pixies have two chars each
    chars_y = pixies_y;

    matrix_width  = display_width  * chars_x;
    matrix_height = display_height * chars_y;

    NUM_PIXELS = matrix_width * matrix_height;

    color_map = new CRGB[ NUM_PIXELS + 1 ]; // Hidden extra LED to write to if we call an out-of-bounds XY coordinate for color or mask
    mask      = new uint8_t[ NUM_PIXELS + 1 ];
    xy_table  = new int16_t[ NUM_PIXELS ];

    calc_xy(); // NUM_LEDS is calculated here

    color_map_out = new CRGB[ NUM_LEDS ];
    mask_out = new uint8_t[ NUM_LEDS ];

    for( uint16_t i = 0; i < NUM_LEDS; i++ ){
        color_map[i] = CRGB( 0, 255, 0 );
    }

    current_palette.loadDynamicGradientPalette( GREEN_SOLID );

    build_controller( pixie_pin ); // ----- Initialize FastLED
    set_animation( ANIMATION_NULL ); // --- Set animation function to an empty one
    clear(); // --------------------------- Clear anything in mask (should be empty anyways), reset cursor
    set_max_power( 5.0, 500 ); // --------- Set default power budget in volts and milliamps (5.0V, 500mA)
}

/*! ############################################################################
    @brief
    Initializes the display buffer, populates the XY coordinate table, defaults
    the display colors to green, loads the default CRGBPalette, initializes
    FastLED **for Quad Mode**, and sets the default power budget.
    
    @details
    This version of begin() is special, in that it will send your image data to
    the LEDs in 4 parallel streams to increase speed.
    
    Unfortunately, this requires hard-coded pins on the ESP8266 and ESP32 to
    function *due to FastLED limitations*:
    
    - DATA_OUT_1:  **GPIO 12 / D6**
    - DATA_OUT_2:  **GPIO 13 / D7**
    - DATA_OUT_3:  **GPIO 14 / D5**
    - DATA_OUT_4:  **GPIO 15 / D8**
    
    On each data line, you'll wire `pixies_per_pin` number of Pixie
    Chromas, with the final image being seamlessly spread across these
    four lines.
    
    For example, if you have 16 Pixie Chromas (in two rows of eight) and
    have Quad Mode enabled, then each of the 4 data lines will have 4
    Pixie Chromas like so:
    
    - **DATA_OUT_1** GPIO
      - Pixie 1
      - Pixie 2
      - Pixie 3
      - Pixie 4
    - **DATA_OUT_2** GPIO
      - Pixie 5
      - Pixie 6
      - Pixie 7
      - Pixie 8
    - **DATA_OUT_3** GPIO
      - Pixie 9
      - Pixie 10
      - Pixie 11
      - Pixie 12
    - **DATA_OUT_4** GPIO
      - Pixie 13
      - Pixie 14
      - Pixie 15
      - Pixie 16
    
    The corresponding setup for this display layout would be:
    
        #include "Pixie_Chroma.h"
        PixieChroma pix;
        
        #define PIXIES_PER_PIN 4
        #define PIXIES_X       8
        #define PIXIES_Y       2
        
        void setup() {
            pix.begin_quad( PIXIES_PER_PIN, PIXIES_X, PIXIES_Y );
        }
    
    Then, with the displays physically arranged in reading order ( left to right,
    top to bottom ) you're ready to begin!

        DATA_OUT_1 --+                       DATA_OUT_2 ----+
                     |                                      |
                  +--+-+   +----+   +----+   +----+  ||  +--+-+   +----+   +----+   +----+
                  |  1 |-->|  2 |-->|  3 |-->|  4 |  ||  |  5 |-->|  6 |-->|  7 |-->|  8 | 
                  +----+   +----+   +----+   +----+  ||  +----+   +----+   +----+   +----+ 

        DATA_OUT_3 --+                       DATA_OUT_4 ----+
                     |                                      |
                  +--+-+   +----+   +----+   +----+  ||  +--+-+   +----+   +----+   +----+
                  |  9 |-->| 10 |-->| 11 |-->| 12 |  ||  | 13 |-->| 14 |-->| 15 |-->| 16 | 
                  +----+   +----+   +----+   +----+  ||  +----+   +----+   +----+   +----+ 
    
    Using begin_quad() to enable the Quad Mode driver will
    always send the 4 lines of data in parallel, saving on time per frame.

    begin_quad() ideally **should not be used with less than 4 Pixie Chromas**,
    and with at least one on each line. Even if only two lines are physically
    used, all 4 pins are still occupied by Quad Mode.
    
    @param  pixies_per_pin  Pixies per data pin
    @param  pixies_x        Number of Pixie PCBs in the X axis of your display
    @param  pixies_y        Number of Pixie PCBs in the Y axis of your display
*///............................................................................
void PixieChroma::begin_quad( uint8_t pixies_per_pin, uint8_t pixies_x, uint8_t pixies_y ){    
    chars_x = pixies_x * 2; // Pixies have two chars each
    chars_y = pixies_y;

    matrix_width  = display_width  * chars_x;
    matrix_height = display_height * chars_y;

    NUM_PIXELS = matrix_width * matrix_height;

    color_map = new CRGB[ NUM_PIXELS + 1 ]; // Hidden extra LED to write to if we call an out-of-bounds XY coordinate for color or mask
    mask      = new uint8_t[ NUM_PIXELS + 1 ];
    xy_table  = new int16_t[ NUM_PIXELS ];

    calc_xy();

    color_map_out = new CRGB[ NUM_LEDS ];
    mask_out = new uint8_t[ NUM_LEDS ];
    
    for( uint16_t i = 0; i < NUM_LEDS; i++ ){
        color_map[i] = CRGB( 0,255,0 );
    }

    current_palette.loadDynamicGradientPalette( GREEN_SOLID );

    #if defined( ARDUINO_ARCH_ESP8266 )
    // WS2811_PORTA on ESP8266 takes up GPIO 12, GPIO 13, GPIO 14 and GPIO 15 for Quad Mode
    FastLED.addLeds<WS2811_PORTA,4>( color_map_out, pixies_per_pin * leds_per_pixie ).setCorrection( TypicalLEDStrip ); // Initialize FastLED
    #endif
    
    #if defined( ARDUINO_ARCH_ESP32 )
    
    // Quad Mode on ESP32 takes up GPIO 12, GPIO 13, GPIO 14 and GPIO 27
    FastLED.addLeds<NEOPIXEL, 13>( // Initialize FastLED Data Out 1
        color_map_out,
        0,
        ( pixies_per_pin*leds_per_pixie )
    ).setCorrection( TypicalLEDStrip ); 
    
    FastLED.addLeds<NEOPIXEL, 12>( // Initialize FastLED Data Out 2
        color_map_out,
        ( pixies_per_pin*leds_per_pixie ),
        ( pixies_per_pin*leds_per_pixie )
    ).setCorrection( TypicalLEDStrip );
    
    FastLED.addLeds<NEOPIXEL, 14>( // Initialize FastLED Data Out 3
        color_map_out,
        ( pixies_per_pin*leds_per_pixie ) * 2,
        ( pixies_per_pin*leds_per_pixie )
    ).setCorrection( TypicalLEDStrip );
    
    FastLED.addLeds<NEOPIXEL, 27>( // Initialize FastLED Data Out 4
        color_map_out,
        ( pixies_per_pin*leds_per_pixie ) * 4,
        ( pixies_per_pin*leds_per_pixie )
    ).setCorrection( TypicalLEDStrip );

    #endif
    
    set_animation( ANIMATION_NULL ); // --- Set animation function to an empty one
    clear(); // --------------------------- Clear anything in mask ( should be empty anyways ), reset cursor
    set_max_power( 5, 500 ); // ----------- Set default power budget in volts and milliamps
}


/*! ############################################################################
    @brief
    Takes an 8-bit brightness value and passes it to FastLED internally, to
    provide global brightness control with temporal dithering.
    
    @param  level  8-bit global brightness value ( 0-255 )
*///............................................................................
void PixieChroma::set_brightness( uint8_t level ){
    brightness_level = level;
}


/*! ############################################################################
    @brief
    Accepts a const uint8_t (8-bit) array to generate a FastLED Gradient
    Palette at runtime:
    
        const uint8_t* my_gradient_palette[] = {
            [INDEX],  [R_VAL],  [G_VAL],  [B_VAL],
        
            0,        255,      0,        0, 
            127,      0,        255,      0, 
            255,      0,        0,        255, 
        };
    
    On each line is the index of the color ( 0-255 ) to express the position in
    the gradient this color occurs. So in the given example, it is a gradient
    from red at 0, to green at 127, to blue at 255.
    
    @param  pal  FastLED "Gradient Palette" array
*///............................................................................
void PixieChroma::set_palette( const uint8_t* pal ){ 
    current_palette.loadDynamicGradientPalette( pal ); // GRADIENT PALETTE
}


/*! ############################################################################
    @brief
    Accepts a FastLED CRGBPalette16 object to set the current color palette for
    animation.
    
    @param  pal  FastLED CRGBPalette16 object to use
*///............................................................................
void PixieChroma::set_palette( CRGBPalette16 pal ){ // STANDARD PALETTE
    current_palette = pal;
}


/*! ############################################################################
    @brief
    Accepts a preset or custom function to use for the animation ISR.
    
    @details
    For a list of predefined animations, see pixie_animations.h.
    
    @param  action  Function to set as an animation ISR
*///............................................................................
void PixieChroma::set_animation( void ( *action )(float) ) {
    anim_func = action;
}


/*! ############################################################################
    @brief
    Used to scale the animation speed of animation ISRs that can use
    pix.animation_speed() to scale their speeds or for other effects
                
    @param  speed  Floating point value: 1.0 = 100%, 3.2 = 320%, 0.5 = 50%
*///............................................................................
void PixieChroma::set_animation_speed( float speed ){
    animation_speed = speed;
}


/*! ############################################################################
    @brief
    Allows you to enable built-in automatic gamma correction, using a fast LUT
    in pixie_utility.h. (Not enabled by default)

    @param  enabled  Whether or not to apply gamma correction
*///............................................................................
void PixieChroma::set_gamma_correction( bool enabled ){
    correct_gamma = enabled;
}


/*! ############################################################################
    @brief
    Sets the cursor position in a 2D context, in whole displays.
    
    @details  
    Wherever the cursor is, is where the next call to print() or write() will
    originate. Position is counted from zero. Remember: each Pixie Chroma has
    two "displays" on it.

        +-----------------+   +-----------------+   +-----------------+
        |      + + +      |   |      + + +      |   |      + + +      |
        |+-----+   +-----+|   |+-----+   +-----+|   |+-----+   +-----+|
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        || 0,0 |   | 1,0 ||-->|| 2,0 |   | 3,0 ||-->|| 4,0 |   | 5,0 ||
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        |+-----+   +-----+|   |+-----+   +-----+|   |+-----+   +-----+|
        |      + + +      |   |      + + +      |   |      + + +      |
        +-----------------+   +-----------------+   +-----------------+
                                                           |
               +-------------------------------------------+
               |
               V
        +-----------------+   +-----------------+   +-----------------+
        |      + + +      |   |      + + +      |   |      + + +      |
        |+-----+   +-----+|   |+-----+   +-----+|   |+-----+   +-----+|
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        || 0,1 |   | 1,1 ||-->|| 2,1 |   | 3,1 ||-->|| 4,0 |   | 5,1 ||
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        ||     |   |     ||   ||     |   |     ||   ||     |   |     ||
        |+-----+   +-----+|   |+-----+   +-----+|   |+-----+   +-----+|
        |      + + +      |   |      + + +      |   |      + + +      |
        +-----------------+   +-----------------+   +-----------------+

    For example:

    `set_cursor( 1,0 )` sets the cursor to the second display in the first row.

    `set_cursor( 3,1 )` sets the cursor to the fourth display in the second row.

    @param  x_position  New cursor position on the X-axis, in whole displays
    @param  y_position  New cursor position on the Y-axis, in whole displays
*///............................................................................
void PixieChroma::set_cursor( uint8_t x_position, uint8_t y_position ){
    cursor_x = ( display_width  * x_position ) + display_padding_x;
    cursor_y = ( display_height * y_position ) + display_padding_y;
}


/*! ############################################################################
    @brief
    Sets the maximum power budget in volts and milliamps.
    
    @details
    Knowing the average power consumption of these LEDs at any given color,
    FastLED will automatically globally scale down the output values with
    temporal dithering to lower power usage until it is within the budget
    defined here. Defaults to 5.0V / 500mA to protect PC USB ports if the
    Pixies are not independently powered. ( 2000mA = 2A, 500mA = 0.5A, etc. )

    @param  volts      Total LED power budget in volts. ( default: 5.0 )
    @param  milliamps  Total LED power budget in milliamps ( default 500 )
*///............................................................................
void PixieChroma::set_max_power( float volts, uint16_t milliamps ){
    max_V = volts;
    max_mA = milliamps;
}


/*! ############################################################################
    @brief
    Sets the target frame rate for animation. This target frame rate is only
    used to calculate `delta` in custom/preset animation functions.
            
    @details
    This does not change your real frame rate, or even govern it: it is left up
    to the user to use frequent show() calls or auto_update(). The "target frame
    rate" here is used to calculate `delta` for the animation functions, and
    should be set as close as possible to the rate at which you are expecting to
    call show().

    This function is automatically called with a matching FPS when you use
    `set_update_mode( AUTOMATIC, FPS )`.

    @param  target  Target frame rate for animation.
*///............................................................................
void PixieChroma::set_frame_rate_target( uint16_t target ){
    fps_target = target;
}


/*! ############################################################################
    @brief
    Sets the line wrapping behavior

    @details
    `set_line_wrap( true );` will automatically enter next line when the edge of
    the display is reached, and `set_line_wrap( false );` will not.

    @param  enabled  Enable or disable auto line-wrapping
*///............................................................................
void PixieChroma::set_line_wrap( bool enabled ){
    line_wrap = enabled;
}


/*! ############################################################################
    @brief
    Allows for automatic show() calls at a specified frames per second if
    AUTOMATIC is used. (uses Ticker.attach_ms() internally)
            
    @details
    This lets you use things like print() as infrequently as you'd like, since
    show() will automatically run in the background to keep the current
    animation function running smoothly.
            
    Use in conjunction with hold() and free() to prevent show() calls during
    text/image construction, leading to unintended partial frames being shown.
    Be aware, hold() does not prevent animation / palette updates (only mask
    updates) so animations will still run smoothly during hold() times until
    free() is called and the mask is finally updated.
    
    @param  mode  AUTOMATIC or MANUAL. AUTOMATIC will call show() at `FPS`
                  using an ISR, MANUAL allows you call show() when you like.

    @param  FPS   Update *this* many times per second (Default: 60) Only
                  applicable when mode is AUTOMATIC
*///............................................................................
void PixieChroma::set_update_mode( t_update_mode mode, uint16_t FPS ){
    if( mode == AUTOMATIC && ticker_running == false ){
        set_frame_rate_target( FPS );
        animate.attach_ms( 1000 / FPS, show_container );
        ticker_running = true;
    }
    else if( mode == MANUAL && ticker_running == true ){
        animate.detach();
        ticker_running = false;
    }
}


/*! ############################################################################
    @brief
    Writes an icon* to a specified X and Y cursor position
    
    @param  icon   The icon to write
    @param  x_pos  X cursor position of write **[optional]**
    @param  y_pos  Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( const uint8_t* icon, uint8_t x_pos, uint8_t y_pos ){
    write_pix(
        icon,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes an icon to a specified X and Y cursor position, taking five uint8_t
    as input for the column data.
    
    @details
    Example:

        pix.write( B00101111, B01001001, B01001001, B01001001, B00110001 );
        
            OR, WRITTEN VERTICALLY:
        
        pix.write(   ,   ,   ,   ,   );
                   1   1   1   1   1  LSB
                   1   0   0   0   0
                   1   0   0   0   0
                   1   1   1   1   0
                   0   0   0   0   1
                   1   0   0   0   1
                   0   1   1   1   0  
                   0   0   0   0   0  MSB (unused)
                   B   B   B   B   B
    
    This writes a "5" to the display, seen above in the "1" bits of each column.
    The MSB (highest bit) is not used in icons.
    
    @param  icon_col_1  Column 1 data of this icon
    @param  icon_col_2  Column 2 data of this icon
    @param  icon_col_3  Column 3 data of this icon
    @param  icon_col_4  Column 4 data of this icon
    @param  icon_col_5  Column 5 data of this icon
    @param  x_pos       X cursor position of write **[optional]**
    @param  y_pos       Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5, uint8_t x_pos, uint8_t y_pos ){
    uint8_t icon[5] = {
        icon_col_1,
        icon_col_2,
        icon_col_3,
        icon_col_4,
        icon_col_5
    };
    write( icon, x_pos, y_pos );
}


/*! ############################################################################
    @brief
    Writes a char* string to a specified X and Y cursor position.
    
    @param  message  char* string to write
    @param  x_pos    X cursor position of write **[optional]**
    @param  y_pos    Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( char* message, uint8_t x_pos, uint8_t y_pos ){
    write_pix(
        message,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes a signed 16-bit integer to a specified X and Y cursor position.
    
    @param  input  Signed integer to write
    @param  x_pos  X cursor position of write **[optional]**
    @param  y_pos  Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( int16_t input, uint8_t x_pos, uint8_t y_pos ){
    char char_buf[32];
    itoa( input, char_buf, 10 );

    write_pix(
        char_buf,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes an unsigned 16-bit integer to a specified X and Y cursor position.
    
    @param  input  Unsigned integer to write
    @param  x_pos  X cursor position of write **[optional]**
    @param  y_pos  Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( uint16_t input, uint8_t x_pos, uint8_t y_pos ){
    char char_buf[32];
    utoa( input, char_buf, 10 );

    write_pix(
        char_buf,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes a signed 32-bit integer to a specified X and Y cursor position.
    
    @param  input  Signed integer to write
    @param  x_pos  X cursor position of write **[optional]**
    @param  y_pos  Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( int32_t input, uint8_t x_pos, uint8_t y_pos ){
    char char_buf[32];
    ltoa( input, char_buf, 10 );

    write_pix(
        char_buf,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes an unsigned 32-bit integer to a specified X and Y cursor position.
    
    @param  input  Unsigned integer to write
    @param  x_pos  X cursor position of write **[optional]**
    @param  y_pos  Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( uint32_t input, uint8_t x_pos, uint8_t y_pos ){
    char char_buf[32];
    ultoa( input, char_buf, 10 );

    write_pix(
        char_buf,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes an unsigned 32-bit integer to a specified X and Y cursor position.
    ( Stupid ESP-specific type )
    
    @param  input  Unsigned integer to write
    @param  x_pos  X cursor position of write **[optional]**
    @param  y_pos  Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( long unsigned int input, uint8_t x_pos, uint8_t y_pos ){
    char char_buf[32];
    ultoa( input, char_buf, 10 );

    write_pix(
        char_buf,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes a double-precision floating point value to a specified X and Y cursor
    position, to a specified number of decimal places.
    
    @param  input   Double-precision float to write
    @param  places  Number of decimal places to show **[optional]**
    @param  x_pos   X cursor position of write **[optional]**
    @param  y_pos   Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( double input, uint8_t places, uint8_t x_pos, uint8_t y_pos ){
    char char_buf[32];
    dtoa( input, char_buf, places );

    write_pix(
        char_buf,
        display_padding_x + ( display_width  * x_pos ),
        display_padding_y + ( display_height * y_pos )
    );
}


/*! ############################################################################
    @brief
    Writes a single-precision floating point value to a specified X and Y cursor
    position, to a specified number of decimal places.
    
    @param  input   Single-precision float to write
    @param  places  Number of decimal places to show **[optional]**
    @param  x_pos   X cursor position of write **[optional]**
    @param  y_pos   Y cursor position of write **[optional]**
*///............................................................................
void PixieChroma::write( float input, uint8_t places, uint8_t x_pos, uint8_t y_pos ){
    write(
        double( input ),
        places,
        x_pos,
        y_pos
    );
}


/*! ############################################################################
    @brief
    Internal function for rendering icons to the mask buffer.
    
    @details
    This can also be used to write Icons that are not aligned to whole display
    positions, such as during smooth scrolling.
    
    @param  icon   Icon to render
    @param  x_pos  X pixel position of write **[optional]**
    @param  y_pos  Y pixel position of write **[optional]**
*///............................................................................
void PixieChroma::write_pix( const uint8_t* icon, int16_t x_offset, int16_t y_offset ){
    add_char(
        icon,
        cursor_x + x_offset,
        cursor_y + y_offset
    );
    cursor_x += display_width;
}


/*! ############################################################################
    @brief
    Internal function for rendering char* strings to the mask buffer.
    
    @details
    All other write() function overloads eventually end up casted to char*
    strings and passed to this function for rendering. This can also be used to
    write char* strings that are not aligned to whole display positions, such
    as during smooth scrolling.
    
    @param  message  char* string to render
    @param  x_pos    X pixel position of write **[optional]**
    @param  y_pos    Y pixel position of write **[optional]**
*///............................................................................
void PixieChroma::write_pix( char* message, int16_t x_offset, int16_t y_offset ){
    uint8_t len = strlen( message );
    for( uint8_t i = 0; i < len; i++ ){
        if( message[i] == '\n' ){ // Newline, force line break
            // TODO: write_pix( char* ) should never modify cursor position
            // Use an internal offset ( +user offset ) to place chars instead
            cursor_x =  display_padding_x;
            cursor_y += display_height;
        }
        else if( line_wrap == true && cursor_x >= ( display_width * chars_x ) ){ // End of line reached, wrap to new line if line_wrap enabled
            cursor_x =  display_padding_x;
            cursor_y += display_height;
            
            add_char(
                message[i],
                cursor_x + x_offset,
                cursor_y + y_offset
            );
            cursor_x += display_width;
        }
        else if( message[i] == 0 || message[i] == '\0' ){ // end of string
            return;
        }
        else{ // Normal
            add_char(
                message[i],
                cursor_x + x_offset,
                cursor_y + y_offset
            );
            cursor_x += display_width;
        }        
    }
}


/*! ############################################################################
    @brief
    Internal function for rendering a single char to the mask buffer.
    
    @details
    All other write() function overloads eventually end up casted to char*
    strings and passed to this function one character at a time for rendering.
    
    @param  chr    char to render
    @param  x_pos  X pixel position of write
    @param  y_pos  Y pixel position of write
*///............................................................................
void PixieChroma::add_char( char chr, int16_t x_pos, int16_t y_pos ){
    if ( chr >= printable_ascii_offset ) {
        chr -= printable_ascii_offset;
    }

    for( uint8_t x = 0; x < font_col_width; x++ ){
        uint8_t column = pgm_read_byte( font + ( chr * font_col_width + x ) );

        uint16_t row1_index = xy( x_pos+x, y_pos+0 );
        uint16_t row2_index = xy( x_pos+x, y_pos+1 );
        uint16_t row3_index = xy( x_pos+x, y_pos+2 );
        uint16_t row4_index = xy( x_pos+x, y_pos+3 );
        uint16_t row5_index = xy( x_pos+x, y_pos+4 );
        uint16_t row6_index = xy( x_pos+x, y_pos+5 );
        uint16_t row7_index = xy( x_pos+x, y_pos+6 );

        // "Subtract" from mask transparency with saturating function
        mask[row1_index] = qadd8( mask[row1_index], bit_table[bitRead( column, 0 )] );
        mask[row2_index] = qadd8( mask[row2_index], bit_table[bitRead( column, 1 )] );
        mask[row3_index] = qadd8( mask[row3_index], bit_table[bitRead( column, 2 )] );
        mask[row4_index] = qadd8( mask[row4_index], bit_table[bitRead( column, 3 )] );
        mask[row5_index] = qadd8( mask[row5_index], bit_table[bitRead( column, 4 )] );
        mask[row6_index] = qadd8( mask[row6_index], bit_table[bitRead( column, 5 )] );
        mask[row7_index] = qadd8( mask[row7_index], bit_table[bitRead( column, 6 )] );
    }
}


/*! ############################################################################
    @brief
    Internal function for rendering a single icon to the mask buffer.
    
    @param  icon   Icon column data to render
    @param  x_pos  X pixel position of write
    @param  y_pos  Y pixel position of write
*///............................................................................
void PixieChroma::add_char( const uint8_t* icon, int16_t x_pos, int16_t y_pos ){
    for( uint8_t x = 0; x < font_col_width; x++ ){
        uint8_t column = pgm_read_byte_far( icon+x );

        uint16_t row1_index = xy( x_pos+x, y_pos+0 );
        uint16_t row2_index = xy( x_pos+x, y_pos+1 );
        uint16_t row3_index = xy( x_pos+x, y_pos+2 );
        uint16_t row4_index = xy( x_pos+x, y_pos+3 );
        uint16_t row5_index = xy( x_pos+x, y_pos+4 );
        uint16_t row6_index = xy( x_pos+x, y_pos+5 );
        uint16_t row7_index = xy( x_pos+x, y_pos+6 );

        // "Subtract" from mask transparency with saturating function
        mask[row1_index] = qadd8( mask[row1_index], bit_table[bitRead( column,0 )] );
        mask[row2_index] = qadd8( mask[row2_index], bit_table[bitRead( column,1 )] );
        mask[row3_index] = qadd8( mask[row3_index], bit_table[bitRead( column,2 )] );
        mask[row4_index] = qadd8( mask[row4_index], bit_table[bitRead( column,3 )] );
        mask[row5_index] = qadd8( mask[row5_index], bit_table[bitRead( column,4 )] );
        mask[row6_index] = qadd8( mask[row6_index], bit_table[bitRead( column,5 )] );
        mask[row7_index] = qadd8( mask[row7_index], bit_table[bitRead( column,6 )] );
    }
}


/*! ############################################################################
    @brief
    Prints an Icon to the displays, at the current cursor position.
    
    @param  icon  Icon column data to render
*///............................................................................
void PixieChroma::print( const uint8_t* icon ){
    write_pix( icon, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints an icon to the displays at the current cursor position, taking five
    uint8_t as input for the column data.
    
    @details
    Example:

        pix.print( B00101111, B01001001, B01001001, B01001001, B00110001 );
        
            OR, WRITTEN VERTICALLY:
        
        pix.print(    ,   ,   ,   ,    );
                    1   1   1   1   1  LSB
                    1   0   0   0   0
                    1   0   0   0   0
                    1   1   1   1   0
                    0   0   0   0   1
                    1   0   0   0   1
                    0   1   1   1   0  
                    0   0   0   0   0  MSB ( unused )
                    B   B   B   B   B
        
    This writes a "5" to the display, seen above in the "1" bits of
    each column. The MSB ( highest bit ) is not used in icons.
              
    @param  icon_col_1  Column 1 data of this icon
    @param  icon_col_2  Column 2 data of this icon
    @param  icon_col_3  Column 3 data of this icon
    @param  icon_col_4  Column 4 data of this icon
    @param  icon_col_5  Column 5 data of this icon
*///............................................................................
void PixieChroma::print( uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5 ){
    const uint8_t icon[5] = {
        icon_col_1,
        icon_col_2,
        icon_col_3,
        icon_col_4,
        icon_col_5,
    };
    write_pix( icon, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints a char* string to the displays at the current cursor position.
    
    @param  message  char* string to print
*///............................................................................
void PixieChroma::print( char* message ){
    write_pix( message, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints a signed 16-bit integer to the displays at the current cursor 
    position.
    
    @param  input  Signed integer to print
*///............................................................................
void PixieChroma::print( int16_t input ){
    char char_buf[32];
    itoa( input, char_buf, 10 );
    write_pix( char_buf, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints an unsigned 16-bit integer to the displays at the current cursor
    position.
    
    @param  input  Unsigned integer to print
*///............................................................................
void PixieChroma::print( uint16_t input ){
    char char_buf[32];
    utoa( input, char_buf, 10 );
    write_pix( char_buf, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints a signed 32-bit integer to the displays at the current cursor
    position.
    
    @param  input  Signed integer to print
*///............................................................................
void PixieChroma::print( int32_t input ){
    char char_buf[32];
    ltoa( input, char_buf, 10 );
    write_pix( char_buf, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints an unsigned 32-bit integer to the displays at the current cursor\
    position.
    
    @param  input  Unsigned integer to print
*///............................................................................
void PixieChroma::print( uint32_t input ){
    char char_buf[32];
    ultoa( input, char_buf, 10 );
    write_pix( char_buf, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints an unsigned 32-bit integer to the displays at the current cursor
    position. ( Dumb ESP-specific type )
    
    @param  input  Unsigned integer to print
*///............................................................................
void PixieChroma::print( long unsigned int input ){
    char char_buf[32];
    ultoa( input, char_buf, 10 );
    write_pix( char_buf, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints a double-precision floating point integer to the displays at the
    current cursor position, to a specified number of decimal places.
    
    @param  input   double to print
    @param  places  Number of decimal places to print **[optional]**
*///............................................................................
void PixieChroma::print( double input, uint8_t places ){
    char char_buf[32];
    dtoa( input, char_buf, places );
    write_pix( char_buf, cursor_x, cursor_y );
}


/*! ############################################################################
    @brief
    Prints a single-precision floating point integer to the displays at the
    current cursor position, to a specified number of decimal places.
    
    @param  input   float to print
    @param  places  Number of decimal places to print **[optional]**
*///............................................................................
void PixieChroma::print( float input, uint8_t places ){
    print( double( input ), places );
}


/*! ############################################################################
    @brief
    Prints an Icon to the displays at the current cursor position, then jumps to
    the next row in the Pixie display, similar to a newline '\\n' character.
    
    @param  icon  Icon column data to print
*///............................................................................
void PixieChroma::println( const uint8_t* icon ){
    write_pix( icon ); // ........ Output
    cursor_x =  display_padding_x;
    cursor_y += display_height;
}


/*! ############################################################################
    @brief
    Prints an Icon to the displays at the current cursor position, (taking five
    uint8_t as input for the column data) then jumps to the next row in the
    Pixie display, similar to a newline '\\n' character.
    
    @param  icon_col_1  Column 1 data of this icon
    @param  icon_col_2  Column 2 data of this icon
    @param  icon_col_3  Column 3 data of this icon
    @param  icon_col_4  Column 4 data of this icon
    @param  icon_col_5  Column 5 data of this icon
*///............................................................................
void PixieChroma::println( uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5 ){
    const uint8_t icon[5] = {
        icon_col_1,
        icon_col_2,
        icon_col_3,
        icon_col_4,
        icon_col_5
    };
    write_pix( icon );
    cursor_x =  display_padding_x;
    cursor_y += display_height;
}


/*! ############################################################################
    @brief
    Prints a char* string to the displays at the current cursor position, then
    jumps to the next row in the Pixie display, similar to a newline '\\n'
    character.
    
    @param  message  char* string to print
*///............................................................................
void PixieChroma::println( char* message ){
    write_pix( message ); // ........ Output
    cursor_x =  display_padding_x;
    cursor_y += display_height;
}


/*! ############################################################################
    @brief
    Prints a signed 16-bit integer to the displays at the current cursor
    position, then jumps to the next row in the Pixie display, similar to a
    newline '\\n' character.
    
    @param  input  Signed 16-bit integer to print
*///............................................................................
void PixieChroma::println( int16_t input ){
    char char_buf[32];
    itoa( input, char_buf, 10 );
    println( char_buf );
}


/*! ############################################################################
    @brief
    Prints an unsigned 16-bit integer to the displays at the current cursor
    position, then jumps to the next row in the Pixie display, similar to a
    newline '\\n' character.
    
    @param  input  Unsigned 16-bit integer to print
*///............................................................................
void PixieChroma::println( uint16_t input ){
    char char_buf[32];
    utoa( input, char_buf, 10 );
    println( char_buf );
}


/*! ############################################################################
    @brief
    Prints a signed 32-bit integer to the displays at the current cursor
    position, then jumps to the next row in the Pixie display, similar to a
    newline '\\n' character.
    
    @param  input  Signed 32-bit integer to print
*///............................................................................
void PixieChroma::println( int32_t input ){
    char char_buf[32];
    ltoa( input, char_buf, 10 );
    println( char_buf );
}


/*! ############################################################################
    @brief
    Prints an unsigned 32-bit integer to the displays at the current cursor
    position, then jumps to the next row in the Pixie display, similar to a
    newline '\\n' character.
    
    @param  input  Unsigned 32-bit integer to print
*///............................................................................
void PixieChroma::println( uint32_t input ){
    char char_buf[32];
    ultoa( input, char_buf, 10 );
    println( char_buf );
}


/*! ############################################################################
    @brief
    Prints an unsigned 32-bit integer to the displays at the current cursor
    position, then jumps to the next row in the Pixie display, similar to a
    newline '\\n' character. ( Stupid ESP-specific type )
    
    @param  input  Unsigned 32-bit integer to print
*///............................................................................
void PixieChroma::println( long unsigned int input ){
    char char_buf[32];
    ultoa( input, char_buf, 10 );
    println( char_buf );
}


/*! ############################################################################
    @brief
    Prints a double-precision floating point integer to the displays at the
    current cursor position (to a specified number of decimal places), then
    jumps to the next row in the Pixie display, similar to a newline '\\n'
    character.
            
    @param  input   double to print
    @param  places  Number of decimal places to print **[optional]**
*///............................................................................
void PixieChroma::println( double input, uint8_t places ){
    char char_buf[32];
    dtoa( input, char_buf, places );
    println( char_buf );
}


/*! ############################################################################
    @brief
    Prints a single-precision floating point integer to the displays at the
    current cursor position (to a specified number of decimal places), then
    jumps to the next row in the Pixie display, similar to a newline '\\n'
    character.

    @param  input   float to print
    @param  places  Number of decimal places to print **[optional]**
*///............................................................................
void PixieChroma::println( float input, uint8_t places ){
    println( double(input), places );
}


/*! ############################################################################
    @brief
    Blurs the mask buffer in both axes by blur_amount.

    @param  blur_amount  Amount to blur
*///............................................................................
void PixieChroma::blur( fract8 blur_amount ){
    blur_x( blur_amount );
    blur_y( blur_amount );
}


/*! ############################################################################
    @brief
    Blurs the mask buffer in the X axis by blur_amount.
            
    @param  blur_amount   Amount to blur
*///............................................................................
void PixieChroma::blur_x( fract8 blur_amount ){
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for(  uint8_t row = 0; row < matrix_height; row++ ) {
        uint8_t carryover = 0;
        for(  uint8_t i = 0; i < matrix_width; i++ ) {
            uint8_t cur = mask[xy( i,row )];
            uint8_t part = cur;
            part = scale8( part, seep );
            cur  = scale8( cur, keep );
            cur  = qadd8( cur,carryover );
            if( i ){
                mask[xy( i-1,row )] = qadd8( mask[xy( i-1,row )],part );
            }
            mask[xy( i,row )] = cur;
            carryover = part;
        }
    }
}


/*! ############################################################################
    @brief
    Blurs the mask buffer in the Y axis by blur_amount.
            
    @param  blur_amount  Amount to blur
*///............................................................................
void PixieChroma::blur_y( fract8 blur_amount ){
    // blur columns
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for(  uint8_t col = 0; col < matrix_width; ++col ) {
        uint8_t carryover = 0;
        for(  uint8_t i = 0; i < matrix_height; ++i ) {            
            uint8_t cur = mask[xy( col,i )];
            uint8_t part = cur;
            part = scale8( part, seep );
            cur  = scale8( cur, keep );
            cur  = qadd8( cur,carryover );
            if( i ){
                mask[xy( col,i-1 )] = qadd8( mask[xy( col,i-1 )],part );
            }
            mask[xy( col,i )] = cur;
            carryover = part;
        }
    }
}


/*! ############################################################################
    @brief
    Darkens the mask buffer by an 8-bit amount. Optionally resets the cursor
    position.
            
    @param  amount        8-bit amount to darken the mask
    @param  reset_cursor  Reset the cursor to 0,0 **[optional]**
*///............................................................................
void PixieChroma::dim( uint8_t amount, bool reset_cursor ){
    if( reset_cursor ){
        set_cursor( 0,0 );
    }
    
    for( uint16_t i = 0; i < NUM_PIXELS; i+=11 ){
        mask[i+0]  = scale8( mask[i+0],  255-amount );
        mask[i+1]  = scale8( mask[i+1],  255-amount );
        mask[i+2]  = scale8( mask[i+2],  255-amount );
        mask[i+3]  = scale8( mask[i+3],  255-amount );
        mask[i+4]  = scale8( mask[i+4],  255-amount );
        mask[i+5]  = scale8( mask[i+5],  255-amount );
        mask[i+6]  = scale8( mask[i+6],  255-amount );
        mask[i+7]  = scale8( mask[i+7],  255-amount );
        mask[i+8]  = scale8( mask[i+8],  255-amount );
        mask[i+9]  = scale8( mask[i+9],  255-amount );
        mask[i+10] = scale8( mask[i+10], 255-amount );
    }
}


/*! ############################################################################
    @brief
    Blurs the color buffer in both axes by blur_amount.
            
    @param  blur_amount  Amount to blur
*///............................................................................
void PixieChroma::color_blur( fract8 blur_amount ){
    color_blur_x( blur_amount );
    color_blur_y( blur_amount );
}


/*! ############################################################################
    @brief
    Blurs the color buffer in the X axis by blur_amount.
            
    @param  blur_amount  Amount to blur
*///............................................................................
void PixieChroma::color_blur_x( fract8 blur_amount ){
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for(  uint8_t row = 0; row < matrix_height; row++ ) {
        uint8_t carryover = 0;
        for(  uint8_t i = 0; i < matrix_width; i++ ) {
            CRGB cur = color_map[xy( i,row )];
            CRGB part = cur;
            part.nscale8(  seep );
            cur.nscale8(  keep );
            cur += carryover;
            if(  i ) color_map[xy( i-1,row )] += part;
            color_map[xy( i,row )] = cur;
            carryover = part;
        }
    }
}


/*! ############################################################################
    @brief
    Blurs the color buffer in the Y axis by blur_amount.
            
    @param  blur_amount  Amount to blur
*///............................................................................
void PixieChroma::color_blur_y( fract8 blur_amount ){
    // blur rows same as columns, for irregular matrix
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for(  uint8_t row = 0; row < matrix_width; row++ ) {
        CRGB carryover = CRGB::Black;
        for(  uint8_t i = 0; i < matrix_height; i++ ) {
            CRGB cur = color_map[xy( i,row )];
            CRGB part = cur;
            part.nscale8(  seep );
            cur.nscale8(  keep );
            cur += carryover;
            if(  i ) color_map[xy( i-1,row )] += part;
            color_map[xy( i,row )] = cur;
            carryover = part;
        }
    }
}


/*! ############################################################################
    @brief
    Darkens the color buffer by an 8-bit amount.
            
    @param  amount  8-bit amount to darken the mask
*///............................................................................
void PixieChroma::color_dim( uint8_t amount ){
    CRGBSet leds_temp( color_map, NUM_PIXELS );
    leds_temp.fadeToBlackBy( amount );
}


/*! ############################################################################
    @brief
    Returns the cursor's X position
    
    @return  The cursor's X position
*///............................................................................
uint8_t PixieChroma::get_cursor_x(){
    return cursor_x / chars_x;
}


/*! ############################################################################
    @brief
    Returns the cursor's Y position
    
    @return  The cursor's Y position
*///............................................................................
uint8_t PixieChroma::get_cursor_y(){
    return cursor_y / chars_y;
}


/*! ############################################################################
    @brief
    Returns the cursor's X position in exact pixel coordinates
    
    @return  The cursor's X position in exact pixel coordinates
*///............................................................................
int16_t PixieChroma::get_cursor_x_exact(){
    return cursor_x;
}


/*! ############################################################################
    @brief
    Returns the cursor's Y position in exact pixel coordinates
    
    @return  The cursor's Y position in exact pixel coordinates
*///............................................................................
int16_t PixieChroma::get_cursor_y_exact(){
    return cursor_y;
}


/*! ############################################################################
    @brief
    Clears (blackens) the current mask buffer and resets the cursor to 0,0
*///............................................................................
void PixieChroma::clear(){
    memset( mask, 0, NUM_PIXELS );
    set_cursor( 0,0 );
}


/*! ############################################################################
    @brief
    This function returns the 1D color_map / mask index of a given 2D coordinate
    in the display matrix.
              
    @details
    The XY Table is generated during `begin()` by an internal function,
    `calc_xy()`. Each cell of the table denotes at what index that physical
    pixel location is inside of the 1D color_map / mask arrays.
    
    For example, here is the XY Table for a single Pixie:
    
    |       |        |        |        |        |        |       |       |        |        |        |        |        |       |
    |-------|--------|--------|--------|--------|--------|-------|-------|--------|--------|--------|--------|--------|-------|
    | *70*  | *71*   | *72*   | *73*   | *74*   | *75*   | *76*  | *77*  | *78*   | *79*   | *80*   | *81*   | *82*   | *83*  |
    | *84*  | *85*   | *86*   | *87*   | *88*   | *89*   | *90*  | *91*  | *92*   | *93*   | *94*   | *95*   | *96*   | *97*  | 
    | *98*  | **0**  | **1**  | **2**  | **3**  | **4**  | *99*  | *100* | **35** | **36** | **37** | **38** | **39** | *101* | 
    | *102* | **5**  | **6**  | **7**  | **8**  | **9**  | *103* | *104* | **40** | **41** | **42** | **43** | **44** | *105* | 
    | *106* | **10** | **11** | **12** | **13** | **14** | *107* | *108* | **45** | **46** | **47** | **48** | **49** | *109* | 
    | *110* | **15** | **16** | **17** | **18** | **19** | *111* | *112* | **50** | **51** | **52** | **53** | **54** | *113* | 
    | *114* | **20** | **21** | **22** | **23** | **24** | *115* | *116* | **55** | **56** | **57** | **58** | **59** | *117* | 
    | *118* | **25** | **26** | **27** | **28** | **29** | *119* | *120* | **60** | **61** | **62** | **63** | **64** | *121* | 
    | *122* | **30** | **31** | **32** | **33** | **34** | *123* | *124* | **65** | **66** | **67** | **68** | **69** | *125* | 
    | *126* | *127*  | *128*  | *129*  | *130*  | *131*  | *132* | *133* | *134*  | *135*  | *136*  | *137*  | *138*  | *139* | 
    | *140* | *141*  | *142*  | *143*  | *144*  | *145*  | *146* | *147* | *148*  | *149*  | *150*  | *151*  | *152*  | *153* |
    
    - **BOLD**   = Visible Pixel
    - **ITALIC** = Invisible Pixel
    
    With this example table, a given XY coordinate of `(3, 4)` would return
    `12`. Thus, modifying the color_map or mask at index `12` would influence
    the pixel at the physical location of `(3, 4)`.
    
    Starting from `0` at the top-left with the first visible pixel, (of the first
    display in the XY Table) the index increases to `69`, (the last visible
    pixel in the matrix) before starting to count invisible pixels at index `70`
    and up through `153`.
    
    With this example table setup, the first 70 indices of color_map / mask are
    visible pixels, and the remaining 84 are invisible. (Simulated margin between
    displays)

    Optionally, the result of this function can be run through a wrapping
    function that allows coordinates out of range to wrap around to the
    opposite side of the 2D matrix.
    
    If wrap is not enabled, any coordinates outside of the display matrix will
    be parsed to a 1D index that is completely unused and unseen.
        
    @param   x     Signed 2D X coordinate
    @param   y     Signed 2D Y coordinate
    @param   wrap  Enable wrapping function **[optional]**
    @return  The 1D index of your 2D coordinate
*///............................................................................
uint16_t PixieChroma::xy( int16_t x, int16_t y, bool wrap ) {
    if( wrap ){
        while( x < 0 ){
            x += matrix_width;
        }
        while( x >= matrix_width ){
            x -= matrix_width;
        }
        while( y < 0 ){
            y += matrix_height;
        }
        while( y >= matrix_height ){
            y -= matrix_height;
        }
    }
    else{
        if( x < 0 ){
            return NUM_PIXELS; // If offscreen without wrap return last led in matrix
        }
        else if( x >= matrix_width ){
            return NUM_PIXELS; // If offscreen without wrap return last led in matrix
        }
        if( y < 0 ){
            return NUM_PIXELS; // If offscreen without wrap return last led in matrix
        }
        else if( y >= matrix_height ){
            return NUM_PIXELS; // If offscreen without wrap return last led in matrix
        }
    }

    // done wrapping / culling, time for transformation
    return xy_table[ ( y * matrix_width ) + x ];
}


/*! ############################################################################
    @brief
    Sets the entire color buffer to a CRGB value.
    
    @details
    Example:
    
        pix.color(  CRGB( 0,255,255 )  );
    
    This would set all displays to cyan, a mix of green and blue.
              
    @param  col  FastLED CRGB color
*///............................................................................
void PixieChroma::color( CRGB col ){
    fill_solid( color_map, NUM_PIXELS, col );
}


/*! ############################################################################
    @brief
    Sets a specific display in the color buffer to a CRGB value.
              
    @details
    Example:
    
        pix.color(  CRGB( 0,255,255 ), 1, 0  );
    
    This would set the **second display of the first row** to cyan, a mix of
    green and blue.
              
    @param  col  FastLED CRGB color
    @param  x    X coordinate of display
    @param  y    y coordinate of display
*///............................................................................
void PixieChroma::color( CRGB col, uint8_t x, uint8_t y ){
    int16_t x_pos = x * display_width  + display_padding_x;
    int16_t y_pos = y * display_height + display_padding_y;
    
    for( uint8_t xi = 0; xi < font_col_width; xi++ ){
        color_map[xy( x_pos+xi, y_pos+0 )] = col;
        color_map[xy( x_pos+xi, y_pos+1 )] = col;
        color_map[xy( x_pos+xi, y_pos+2 )] = col;
        color_map[xy( x_pos+xi, y_pos+3 )] = col;
        color_map[xy( x_pos+xi, y_pos+4 )] = col;
        color_map[xy( x_pos+xi, y_pos+5 )] = col;
        color_map[xy( x_pos+xi, y_pos+6 )] = col;
    }
}


/*! ############################################################################
    @brief
    Sets a rectangular area in the color buffer to a CRGB value.
              
    @details
    Example:
    
        pix.color(  CRGB( 0,255,255 ), 0, 0, 5, 5  );
    
    This would set **the first five columns and rows** of the color buffer to
    cyan, a mix of green and blue.
              
    @param    col  FastLED CRGB color
    @param    x1   Starting X coordinate of the rectangle
    @param    y1   Starting Y coordinate of the rectangle
    @param    x2   Ending X coordinate of the rectangle ( inclusive )
    @param    y2   Ending Y coordinate of the rectangle ( inclusive )
*///............................................................................
void PixieChroma::color( CRGB col, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2 ){
    if( x2 < x1 || y2 < y1 ){
        return;
    }

    // Make rectangle selection inclusive
    x2 += 1;
    y2 += 1;
    
    int16_t x1_pos = x1 * display_width  + display_padding_x;
    int16_t y1_pos = y1 * display_height + display_padding_y;
    
    int16_t x2_pos = x2 * display_width  + display_padding_x;
    int16_t y2_pos = y2 * display_height + display_padding_y;

    uint16_t x_delta = x2_pos - x1_pos;
    uint16_t y_delta = y2_pos - y1_pos;
    
    for( uint16_t y = 0; y < y_delta; y++ ){
        for( uint16_t x = 0; x < x_delta; x++ ){
            int16_t x2_pos = x1_pos + x;
            int16_t y2_pos = y1_pos + y;
            color_map[xy( x2_pos, y2_pos )] = col;
        }
    }
}


/*! ############################################################################
    @brief
    Draws a line in the mask buffer using Bresenham's line algorithm.
        
    @param  x1  Starting X coordinate of the line
    @param  y1  Starting Y coordinate of the line
    @param  x2  Ending X coordinate of the line ( inclusive )
    @param  y2  Ending Y coordinate of the line ( inclusive )
*///............................................................................
void PixieChroma::draw_line( int16_t x1, int16_t y1, int16_t x2, int16_t y2 ){
    //Bresenham's line algorithm
    uint16_t index;
    
    int16_t x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
    dx=x2-x1;
    dy=y2-y1;
    dx1=fabs( dx );
    dy1=fabs( dy );
    px=2*dy1-dx1;
    py=2*dx1-dy1;
    if( dy1<=dx1 ){
        if( dx>=0 ){
            x=x1;
            y=y1;
            xe=x2;
        }
        else{
            x=x2;
            y=y2;
            xe=x1;
        }
        index = xy( x,y );
        mask[index] = qadd8(  255, mask[index]  );
        for( i=0;x<xe;i++ ){
            x=x+1;
            if( px<0 ){
                px=px+2*dy1;
            }
            else{
                if( ( dx<0 && dy<0 ) || ( dx>0 && dy>0 ) ){
                    y=y+1;
                }
                else{
                    y=y-1;
                }
                px=px+2*( dy1-dx1 );
            }
            delay( 0 );
            index = xy( x,y );
            mask[index] = qadd8(  255, mask[index]  );
        }
    }
    else{
        if( dy>=0 ){
            x=x1;
            y=y1;
            ye=y2;
        }
        else{
            x=x2;
            y=y2;
            ye=y1;
        }
        index = xy( x,y );
        mask[index] = qadd8(  255, mask[index]  );
        for( i=0;y<ye;i++ ){
            y=y+1;
            if( py<=0 ){
                py=py+2*dx1;
            }
            else{
                if( ( dx<0 && dy<0 ) || ( dx>0 && dy>0 ) ){
                    x=x+1;
                }
                else{
                    x=x-1;
                }
                py=py+2*( dx1-dy1 );
            }
            index = xy( x,y );
            mask[index] = qadd8(  255, mask[index]  );
        }
    }
}


/*! ############################################################################
    @brief
    Approximates the conversion of a blackbody radiation temperature (i.e.
    3500K) to a CRGB color object.
    
    @details
    This can be used within other Pixie color functions like so:
    
        pix.color(  kelvin_to_rgb(  3000  )  );
              
    This would render a warm-white color. This measurement system is often used
    in household LED bulbs, with colors like:

    - 2700K - **Very Warm White**
    - 3500K - **Warm White**
    - 5000K - **White**
    - 7000K - **Cool White**

    @param   temperature  Blackbody radiation temperature in Kelvin
    @return  Approximate CRGB representation of the given temperature
*///............................................................................
CRGB PixieChroma::kelvin_to_rgb( uint16_t temperature ){
    // Tanner Helland formula
    float _temperature;
    float _red;
    float _green;
    float _blue;

    _temperature = constrain( temperature, 0, 65500 );

    _red = _green = _blue = 0;  
    float t = _temperature * 0.01;

    if ( t <= 66 ){
        _red = 255;
        _green = ( 99.4708025861 * log( t ) ) - 161.1195681661;
        if ( t > 19 ){
            _blue = ( 138.5177312231 * log( t - 10 ) ) - 305.0447927307;
        }
        else{
            _blue = 0;
        }
    }
    else{
        _red   = 329.698727466  * pow( t - 60, -0.1332047592 );
        _green = 288.1221695283 * pow( t - 60, -0.0755148492 );
        _blue  = 255;
    }

    float f = 0.01 * 100;

    _red   = constrain( f * _red,   0, 255 );
    _green = constrain( f * _green, 0, 255 );
    _blue  = constrain( f * _blue,  0, 255 );

    return CRGB( _red, _green, _blue );
}


/*! ############################################################################
    @brief
    Freezes the current mask buffer in memory to prevent showing unfinished text
    if show() automaticall fires during construction of the current display data.
    
    Use free() to unfreeze.
*///............................................................................
void PixieChroma::hold(){
    freeze = true;
}


/*! ############################################################################
    @brief
    Unfreezes the current mask buffer in memory to allow showing updated text the
    next time show() is called.
*///............................................................................
void PixieChroma::free(){
    freeze = false;
}


/*! ############################################################################
    @brief
    Processes 1D image data into truncated versions, sending them to the Pixie
    Chroma displays.
            
    @details
    ***FastLED.show() is called here.***
*///............................................................................
void PixieChroma::show(){
    uint32_t t_now = micros();
    float frame_delta_us = t_now-t_last;
    frame_rate = 1000000.0 / frame_delta_us;
    delta = fps_target / frame_rate;
    t_last = t_now;
    
    anim_func( delta ); // Call custom animation function
    
    noInterrupts(); //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    if( !freeze ){ // If we're not holding out for a pix.free() call, show with the current mask
        memcpy( mask_out, mask, NUM_LEDS );
    }
    memcpy( color_map_out, color_map, sizeof( CRGB )*NUM_LEDS );

    for( uint16_t i = 0; i < NUM_LEDS; i++ ){
        // MASKING
        color_map_out[i].fadeLightBy( 255-mask_out[i] ); // Apply mask "over" LED color layer
        
        // GAMMA CORRECTION
        if( correct_gamma ){                    
            color_map_out[i].r = gamma8[ color_map_out[i].r ]; // Apply gamma correction LUT
            color_map_out[i].g = gamma8[ color_map_out[i].g ];
            color_map_out[i].b = gamma8[ color_map_out[i].b ];
        }
    }
        
    // Regulate brightness to keep power within budget set with pix.set_max_power( V, mA );
    FastLED.setBrightness( calculate_max_brightness_for_power_vmA( color_map_out, NUM_LEDS, brightness_level, max_V, max_mA ) );
    FastLED.show();

    interrupts(); //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$%
}

/*! ############################################################################
    @brief
    Prints the index table for the calculated XY map. **Requires Serial.begin()
    first to function.**
    
    @details
    Useful for debugging, the index table (XY Map) can be printed over Serial.
    Each cell of the table denotes at what index that physical pixel location is
    inside of the 1D color_map / mask arrays. (The xy() function uses this table
    to translate real-world 2D coordinates to 1D indices.)
    
    For example, here is the XY Table for a single Pixie:
    
    |       |        |        |        |        |        |       |       |        |        |        |        |        |       |
    |-------|--------|--------|--------|--------|--------|-------|-------|--------|--------|--------|--------|--------|-------|
    | *70*  | *71*   | *72*   | *73*   | *74*   | *75*   | *76*  | *77*  | *78*   | *79*   | *80*   | *81*   | *82*   | *83*  |
    | *84*  | *85*   | *86*   | *87*   | *88*   | *89*   | *90*  | *91*  | *92*   | *93*   | *94*   | *95*   | *96*   | *97*  | 
    | *98*  | **0**  | **1**  | **2**  | **3**  | **4**  | *99*  | *100* | **35** | **36** | **37** | **38** | **39** | *101* | 
    | *102* | **5**  | **6**  | **7**  | **8**  | **9**  | *103* | *104* | **40** | **41** | **42** | **43** | **44** | *105* | 
    | *106* | **10** | **11** | **12** | **13** | **14** | *107* | *108* | **45** | **46** | **47** | **48** | **49** | *109* | 
    | *110* | **15** | **16** | **17** | **18** | **19** | *111* | *112* | **50** | **51** | **52** | **53** | **54** | *113* | 
    | *114* | **20** | **21** | **22** | **23** | **24** | *115* | *116* | **55** | **56** | **57** | **58** | **59** | *117* | 
    | *118* | **25** | **26** | **27** | **28** | **29** | *119* | *120* | **60** | **61** | **62** | **63** | **64** | *121* | 
    | *122* | **30** | **31** | **32** | **33** | **34** | *123* | *124* | **65** | **66** | **67** | **68** | **69** | *125* | 
    | *126* | *127*  | *128*  | *129*  | *130*  | *131*  | *132* | *133* | *134*  | *135*  | *136*  | *137*  | *138*  | *139* | 
    | *140* | *141*  | *142*  | *143*  | *144*  | *145*  | *146* | *147* | *148*  | *149*  | *150*  | *151*  | *152*  | *153* |
    
    - **BOLD**   = Visible Pixel
    - **ITALIC** = Invisible Pixel
    
    Starting from `0` at the top-left with the first visible pixel, (of the first
    display in the XY Table) the index increases to `69`, (the last visible
    pixel in the matrix) before starting to count invisible pixels at index `70`
    and up through `153`.
    
    With this example table setup, the first 70 indices of color_map / mask are
    visible pixels, and the remaining 84 are invisible. (Simulated margin between
    displays)
    
*///............................................................................
void PixieChroma::print_xy_table(){
    for( uint8_t y = 0; y < matrix_height; y++ ){
        for( uint8_t x = 0; x < matrix_width; x++ ){
            uint16_t index = ( matrix_width*y )+x;
            Serial.print( xy_table[index] );
            Serial.print( '\t' );
        }
        Serial.println();
    }
}

// ---------------------------------------------------------------------------------------------------------|
// -- PRIVATE CLASS FUNCTIONS ------------------------------------------------------------------------------|
// ---------------------------------------------------------------------------------------------------------|

void PixieChroma::build_controller( const uint8_t pin ){
    // FastLED control pin has to be defined as a constant, ( not just declared const, it's weirdly different ) so
    // this is a hacky workaround. Since we have to hardwire the damn pin number variable, we also have
    // to be careful of the current architecture we're compiling to, since FastLED doesn't let you 
    // define non-existent pins either.
    
    #ifdef ESP8266
        if ( pin == 0 ){FastLED.addLeds<WS2812B, 0, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 1 ){FastLED.addLeds<WS2812B, 1, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 2 ){FastLED.addLeds<WS2812B, 2, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 3 ){FastLED.addLeds<WS2812B, 3, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 4 ){FastLED.addLeds<WS2812B, 4, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 5 ){FastLED.addLeds<WS2812B, 5, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
            // annnnd a bunch of missing pins that are tied to external flash...
        if ( pin == 12 ){FastLED.addLeds<WS2812B, 12, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 13 ){FastLED.addLeds<WS2812B, 13, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 14 ){FastLED.addLeds<WS2812B, 14, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 15 ){FastLED.addLeds<WS2812B, 15, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 16 ){FastLED.addLeds<WS2812B, 16, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
    #endif
    
    #ifdef ESP32
        if ( pin == 0 ){FastLED.addLeds<WS2812B, 0, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 1 ){FastLED.addLeds<WS2812B, 1, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 2 ){FastLED.addLeds<WS2812B, 2, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 3 ){FastLED.addLeds<WS2812B, 3, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 4 ){FastLED.addLeds<WS2812B, 4, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 5 ){FastLED.addLeds<WS2812B, 5, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 12 ){FastLED.addLeds<WS2812B, 12, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 13 ){FastLED.addLeds<WS2812B, 13, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 14 ){FastLED.addLeds<WS2812B, 14, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 15 ){FastLED.addLeds<WS2812B, 15, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 16 ){FastLED.addLeds<WS2812B, 16, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 17 ){FastLED.addLeds<WS2812B, 17, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 18 ){FastLED.addLeds<WS2812B, 18, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 19 ){FastLED.addLeds<WS2812B, 19, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 21 ){FastLED.addLeds<WS2812B, 21, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 22 ){FastLED.addLeds<WS2812B, 22, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 23 ){FastLED.addLeds<WS2812B, 23, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 25 ){FastLED.addLeds<WS2812B, 25, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 26 ){FastLED.addLeds<WS2812B, 26, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 27 ){FastLED.addLeds<WS2812B, 27, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 32 ){FastLED.addLeds<WS2812B, 32, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 33 ){FastLED.addLeds<WS2812B, 33, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
    #endif
    
    #ifdef SAMD_SERIES
        if ( pin == 0 ){FastLED.addLeds<WS2812B, 0, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 1 ){FastLED.addLeds<WS2812B, 1, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 2 ){FastLED.addLeds<WS2812B, 2, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 3 ){FastLED.addLeds<WS2812B, 3, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 4 ){FastLED.addLeds<WS2812B, 4, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 5 ){FastLED.addLeds<WS2812B, 5, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 6 ){FastLED.addLeds<WS2812B, 6, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 7 ){FastLED.addLeds<WS2812B, 7, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 8 ){FastLED.addLeds<WS2812B, 8, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 9 ){FastLED.addLeds<WS2812B, 9, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
        if ( pin == 10 ){FastLED.addLeds<WS2812B, 10, GRB>( color_map_out, NUM_LEDS ).setCorrection( TypicalLEDStrip );}
    #endif
}


void PixieChroma::calc_xy(){
  // Initialize XY table
    for( uint16_t yi = 0; yi < chars_y; yi++ ){
        for( uint16_t y = 0; y < 11; y++ ){
            for( uint16_t xi = 0; xi < chars_x; xi++ ){
                for( uint16_t x = 0; x < 7; x++ ){
                    int16_t x_pos = ( xi*display_width )+x;
                    int16_t y_pos = ( yi*display_height )+y;

                    int16_t x_pos_mod = x_pos % display_width;
                    int16_t y_pos_mod = y_pos % display_height;

                    uint16_t i_table = ( y_pos * matrix_width ) + x_pos;
                    uint16_t i_template = ( y_pos_mod * display_width ) + x_pos_mod;

                    xy_table[i_table] = int8_t( pgm_read_byte( xy_template + i_template ) );
                }
            }
        }
    }

    //Serial.println( "SOLVING VISIBLE" );

    // Initialize first row of displays
    uint8_t visible_rows = 0;
    for( uint16_t row = 0; row < display_height; row++ ){
        uint16_t index = ( 5*visible_rows );
        bool found_visible = false;
        int16_t last_data = 0;
        for( uint16_t col = 0; col < matrix_width; col++ ){
            uint16_t i = ( row*matrix_width )+col;
            int16_t map_data = xy_table[i];

            if( map_data == -1 ){
                xy_table[i] = index;
                index++;
                found_visible = true;
            }

            else if( map_data == -2 ){
                if( last_data == -1 ){
                    index+=30;
                }
            }

            last_data = map_data;
        }

        if( found_visible ){
            visible_rows++;
        }
    }

    NUM_LEDS = 35*chars_x; // account for first row

    // Solve additional rows
    if( chars_y > 1 ){
        uint8_t rows_left = chars_y-1;
        uint16_t row_length = ( display_width*display_height )*chars_x;
        for( uint8_t ii = 0; ii < rows_left; ii++ ){
            for( uint16_t r = 0; r < row_length; r++ ){
                uint16_t final_src_index = ( ii*row_length )+r;
                int16_t src_data = xy_table[final_src_index];
                if( src_data >= 0 ){
                    src_data += ( 35*chars_x );

                    if( src_data > NUM_LEDS ){
                        NUM_LEDS = src_data+1;
                    }
                    xy_table[final_src_index+row_length] = src_data;
                }
            }
        }
    }

    uint16_t index = NUM_LEDS;

    //Serial.println( "SOLVING INVISIBLE" );
    for( uint16_t y = 0; y < matrix_height; y++ ){
        for( uint16_t x = 0; x < matrix_width; x++ ){
            uint16_t i = ( y * matrix_width ) + x;
            uint16_t j = xy_table[i];

            if( xy_table[i] == -2 ){
                xy_table[i] = index;
                index++;
            }
        }
    }
    //Serial.println( "DONE" );
}
