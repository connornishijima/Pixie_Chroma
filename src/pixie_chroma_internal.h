/*!
 * @file pixie_chroma_internal.h
 *
 * Designed specifically to work with Pixie Chroma:
 * ----> https://connornishijima.github.io/PixieChroma
 *
 * Last Updated by Connor Nishijima on 10/20/21 
 */

#ifndef pixie_chroma_h
#define pixie_chroma_h

#include "Arduino.h"

// TODO: Add set_print_color(CRGB) function
// This allows manual color to be automatically applied during subsequent print() calls.
// 
// Usage:
//     set_print_color( CRGB::Red );
//     print( "RED " );   
//     print( "color!" ); // Prints in red
//     set_print_color( CRGB::Green );
//     print( "GREEN " );   
//     print( "color!" ); // Prints in green


/*! Modes for updating Pixie Chroma displays */
enum t_update_mode {
	AUTOMATIC, /*!< Will call show() at a specified FPS using an ISR */
	MANUAL     /*!< Allows you call show() when you like */
};

/*! All text justification options */
enum t_justification {
	LEFT,
	CENTER,
	RIGHT
};

/*! ############################################################################
    @brief
    This is the software documentation for using Pixie Chroma functions on
    Arduino! **For full example usage, see File > Examples > Pixie_Chroma
	inside Arduino!**.
*///............................................................................
class PixieChroma{
	public:
		/** @brief Construct a Pixie Chroma class object */
		PixieChroma(); 
		
		/*+-- Functions - Setup ------------------------------------------------------------*/ 
		/*|*/ void begin( const uint8_t data_pin, uint8_t pixies_x, uint8_t pixies_y );
		/*|*/ void begin_quad( uint8_t pixies_per_pin, uint8_t pixies_x, uint8_t pixies_y );
		/*|*/ void set_brightness( uint8_t level );
		/*|*/ void set_palette( const uint8_t* pal );
		/*|*/ void set_palette( CRGBPalette16 pal );
		/*|*/ void set_animation( void ( *action )( PixieChroma*, float ) );
		/*|*/ void set_animation_speed( float speed );
		/*|*/ void set_gamma_correction( bool enabled );
		/*|*/ void set_max_power( float volts, uint16_t milliamps );
		/*|*/ void set_frame_rate_target( uint16_t target );
		/*|*/ void set_line_wrap( bool enabled );
		/*|*/ void set_justification( t_justification justification, int16_t row = -1 );
		/*|*/ void set_update_mode( t_update_mode mode, uint16_t FPS = 60 );
		/*+---------------------------------------------------------------------------------*/ 
		
		/*+-- Functions - write(  ) ----------------------------------------------------------*/ 
		/*|*/ void write( uint8_t bitmap_col_1, uint8_t bitmap_col_2, uint8_t bitmap_col_3, uint8_t bitmap_col_4, uint8_t bitmap_col_5, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		/*|*/ void write( char* message, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		/*|*/ void write( int16_t input, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		/*|*/ void write( uint16_t input, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		/*|*/ void write( int32_t input, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		/*|*/ void write( uint32_t input, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		#ifndef ARDUINO_ARCH_TEENSY_3_X
		/*|*/ void write( long unsigned int input, uint8_t x_pos = 0, uint8_t y_pos = 0 ); // pretty much the same as uint32_t, but Arduino is stupid
		#endif
		/*|*/ void write( float input, uint8_t places = 2, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		/*|*/ void write( double input, uint8_t places = 2, uint8_t x_pos = 0, uint8_t y_pos = 0 );
		/*|*/ 
		/*|*/ void write_pix( char* message, int16_t x_offset = 0, int16_t y_offset = 0 );
		/*|*/ void write_pix( uint8_t bitmap_col_1, uint8_t bitmap_col_2, uint8_t bitmap_col_3, uint8_t bitmap_col_4, uint8_t bitmap_col_5, int16_t x_dest = 0, int16_t y_dest = 0 );
		/*|*/ 
		/*|*/ void add_char( char chr, int16_t x_pos, int16_t y_pos );
		/*|*/ void add_char( uint8_t bitmap_col_1, uint8_t bitmap_col_2, uint8_t bitmap_col_3, uint8_t bitmap_col_4, uint8_t bitmap_col_5, int16_t x_pos, int16_t y_pos );
		/*+---------------------------------------------------------------------------------*/ 

		/*+-- Functions - print(  ) ----------------------------------------------------------*/ 
		/*|*/ void print( uint8_t bitmap_col_1, uint8_t bitmap_col_2, uint8_t bitmap_col_3, uint8_t bitmap_col_4, uint8_t bitmap_col_5 );
		/*|*/ void print( char chr );
		/*|*/ void print( char* message );
		/*|*/ void print( int16_t input );
		/*|*/ void print( uint16_t input );
		/*|*/ void print( int32_t input );
		/*|*/ void print( uint32_t input );
		#ifndef ARDUINO_ARCH_TEENSY_3_X
		/*|*/ void print( long unsigned int input ); // pretty much the same as uint32_t, but Arduino is stupid
		#endif
		/*|*/ void print( float input, uint8_t places = 2 );
		/*|*/ void print( double input, uint8_t places = 2 );
		/*+---------------------------------------------------------------------------------*/ 

		/*+-- Functions - println(  ) --------------------------------------------------------*/ 	
		/*|*/ void println( uint8_t bitmap_col_1, uint8_t bitmap_col_2, uint8_t bitmap_col_3, uint8_t bitmap_col_4, uint8_t bitmap_col_5 );
		/*|*/ void println( char* message );
		/*|*/ void println( int16_t input );
		/*|*/ void println( uint16_t input );
		/*|*/ void println( int32_t input );
		/*|*/ void println( uint32_t input );
		#ifndef ARDUINO_ARCH_TEENSY_3_X
		/*|*/ void println( long unsigned int input ); // pretty much the same as uint32_t, but Arduino is stupid
		#endif
		/*|*/ void println( float input, uint8_t places = 2 );
		/*|*/ void println( double input, uint8_t places = 2 );
		/*+---------------------------------------------------------------------------------*/

		/*+-- Functions - Cursor -----------------------------------------------------------*/ 
		/*|*/ void    set_cursor( uint8_t x_position, uint8_t y_position = 0 );
		/*|*/ uint8_t get_cursor_x();
		/*|*/ uint8_t get_cursor_y();
		/*|*/ int16_t get_cursor_x_exact();
		/*|*/ int16_t get_cursor_y_exact();
		/*+---------------------------------------------------------------------------------*/
		
		/*+-- Functions - Updating the mask/LEDS -------------------------------------------*/
		/*|*/ void clear();
		/*|*/ void show();
		/*|*/ void hold();
		/*|*/ void free();
		/*+---------------------------------------------------------------------------------*/
		
		/*+-- Functions - Color ------------------------------------------------------------*/ 
		/*|*/ void color( CRGB col ); // Set all displays
		/*|*/ void color( CRGB col, uint8_t x, uint8_t y ); // Set one display
		/*|*/ void color( CRGB col, int16_t x1, int16_t y1, int16_t x2, int16_t y2 ); // Set a 2D rectangle
		/*|*/ CRGB kelvin_to_rgb( uint16_t temperature ); // Get an approximate CRGB ( not yet gamma corrected ) of a blackbody radiation temperature
		/*+---------------------------------------------------------------------------------*/

		/*+-- Functions - Mask Effects -----------------------------------------------------*/ 
		/*|*/ void dim( uint8_t amount, bool reset_cursor = false ); // Fade towards black by amount
		/*|*/ void blur( fract8 blur_amount );
		/*|*/ void blur_x( fract8 blur_amount );
		/*|*/ void blur_y( fract8 blur_amount );
		/*+---------------------------------------------------------------------------------*/
		
		/*+-- Functions - Color Effects ----------------------------------------------------*/ 
		/*|*/ void color_dim( uint8_t amount ); // Fade towards black by amount
		/*|*/ void color_blur( fract8 blur_amount );
		/*|*/ void color_blur_x( fract8 blur_amount );
		/*|*/ void color_blur_y( fract8 blur_amount );
		/*+---------------------------------------------------------------------------------*/

		/*+-- Functions - 2D Tools ---------------------------------------------------------*/ 
		/*|*/ uint16_t xy( int32_t x, int32_t y, bool wrap = false );
		/*|*/ uint16_t uv( float x, float y, bool wrap = false );
		/*|*/ float    get_uv_x( int32_t x_pixel );
		/*|*/ float    get_uv_y( int32_t y_pixel );
		/*|*/ void     shift_mask_x( int16_t amount, int16_t row = -1 );
		/*|*/ void     shift_mask_y( int16_t amount );
		/*|*/ uint8_t  get_pixel_mask( int32_t x, int32_t y );
		/*|*/ void     set_pixel_mask( int32_t x, int32_t y, uint8_t value );
		/*|*/ CRGB     get_pixel_color( int32_t x, int32_t y );
		/*|*/ void     set_pixel_color( int32_t x, int32_t y, CRGB color );
		/*|*/ void     draw_line_mask( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value = 255 );
		/*|*/ void     draw_line_color( int16_t x1, int16_t y1, int16_t x2, int16_t y2, CRGB color );
		/*|*/ void     print_xy_table();
		/*+---------------------------------------------------------------------------------*/
		
		/*+-- Functions - Developer --------------------------------------------------------*/ 
		/*|*/ bool unit_tests();
		/*+---------------------------------------------------------------------------------*/

		// Variables -------------------------------------------------------------------------

        /*! ############################################################################
        @brief
        Contains the entire color map, including "invisible" areas.
        @details
        Note: Pixie Chroma uses "invisible" pixels acting as padding between displays,
        to allow for spatial consistency. (i.e. If a word starts to scroll off the left
        side of one display, it will enter an "invisible" margin before it arrives on
        the next display.
        
            X = Visible
            . = Invisible
        
            . . . . . . . . . . . . . .
            . . . . . . . . . . . . . .
            . X X X X X . . X X X X X .
            . X X X X X . . X X X X X .
            . X X X X X . . X X X X X .
            . X X X X X . . X X X X X .
            . X X X X X . . X X X X X .
            . X X X X X . . X X X X X .
            . X X X X X . . X X X X X .
            . . . . . . . . . . . . . .
            . . . . . . . . . . . . . .
        
		*///............................................................................
        CRGB *color_map;
    
        /*! ############################################################################
        @brief
        Contains the entire mask, including "invisible" areas.
        @details
        The "mask" is used like a semi-transparent overlay over the color map. Imagine
        that you had a red piece of paper: if you took a marker and blacked out all
        areas of the paper except for a circle in the center, it would appear as if
        there was a *red* circle painted on a *black* paper. This is essentially what
        the mask here is doing: subtracting from the output of the color map, to show
        text or bitmaps.
        
        Note: Pixie Chroma uses "invisible" pixels acting as padding between displays,
        to allow for spatial consistency. (i.e. If a word starts to scroll off the left
        side of one display, it will enter an "invisible" margin before it arrives on
        the next display. (See `CRGB *color_map`.)
        
		*///............................................................................
        uint8_t *mask;
    
        /*! ############################################################################
        @brief
        The current FastLED CRGBPalette16 used for animations.
		*///............................................................................
        CRGBPalette16 current_palette;
        
        /*! ############################################################################
        @brief
        Stores the final width of the matrix, including invisible pixels.
		*///............................................................................
		uint16_t matrix_width;
    
        /*! ############################################################################
        @brief
        Stores the final height of the matrix, including invisible pixels.
		*///............................................................................
		uint16_t matrix_height;

        /*! ############################################################################
        @brief
        Stores the total number of pixels, including invisible pixels.
        @details
        This is calculated for you with the display size given to begin().
		*///............................................................................
		uint16_t pixel_count;
    
        /*! ############################################################################
        @brief
        Stores the total number of physical LEDs, not including invisible pixels. This 
        is calculated for you during begin() with an internal function, calc_xy().
		*///............................................................................
		uint16_t led_count;
		
        /*! ############################################################################
        @brief
        Used by animation functions as a way of self-regulating speed if performance
        drops, similar to a game engine.
		*///............................................................................
        float delta = 1.0;
    
        /*! ############################################################################
        @brief
        Used by animation functions to scale the apparent speed of animation.
		*///............................................................................
		float animation_speed = 1.0;
		
		/*! ############################################################################
        @brief
        Allows the user to access a live frame rate calculation (1 frame latency)
		*///............................................................................
		float frame_rate;
		
	private:
		// Functions ----------------------------------
		void build_controller( const uint8_t pin );
		void calc_xy();
		void fetch_shortcode( char* message, uint16_t code_start, uint16_t code_end );
		int16_t calc_justification( t_justification justification, uint8_t row );
		
		// Variables ----------------------------------
		#if defined( ARDUINO_ARCH_ESP8266 ) || defined( ARDUINO_ARCH_ESP32 )
			Ticker animate;
		#elif defined( ARDUINO_ARCH_TEENSY_3_X )
			IntervalTimer animate;
		#endif

		const uint8_t display_padding_x = 1;
		const uint8_t display_padding_y = 2;
		const uint8_t display_width     = display_padding_x + 5 + display_padding_x;
		const uint8_t display_height    = display_padding_y + 7 + display_padding_y;
		const uint8_t leds_per_pixie    = 70;
		const uint8_t bit_table[2]      = {0,255};

        volatile int16_t cursor_x;
		volatile int16_t cursor_y;
		volatile int16_t cursor_x_temp;
		volatile int16_t cursor_y_temp;
		t_justification justifications[8] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT
		};
		
    
        CRGB *color_map_out;
        uint8_t *mask_out;
        int16_t *xy_table;
        uint32_t t_last;

        float    max_V  = 5;
		uint16_t max_mA = 500;    
		uint8_t brightness_level = 255;
        
		bool correct_gamma = false;
		bool line_wrap = true;
		
		bool freeze = false;
		bool ticker_running = false;
		float fps_target = 60;
		
        uint8_t pixie_pin;
		uint8_t chars_x;
		uint8_t chars_y;
		
};

#endif
