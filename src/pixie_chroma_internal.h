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

/*! Modes for updating Pixie Chroma displays */
enum t_update_mode {
	AUTOMATIC, /*!< Will call show() at a specified FPS using an ISR */
	MANUAL     /*!< Allows you call show() when you like */
};

/*!
    @brief  Class that stores functions for interacting with
            Pixie Chroma displays.
*/
class PixieChroma{
	public:
		/** @brief Construct a Pixie Chroma class object */
		PixieChroma(); 
		
		/*+-- Functions - Setup ------------------------------------------------------------*/ 
		/*|*/ void begin(const uint8_t data_pin, uint8_t pixies_x, uint8_t pixies_y);
		/*|*/ void begin_quad(uint8_t pixies_per_pin, uint8_t pixies_x, uint8_t pixies_y);
		/*|*/ void set_brightness(uint8_t level);
		/*|*/ void set_palette(const uint8_t* pal);
		/*|*/ void set_palette(CRGBPalette16 pal);
		/*|*/ void set_animation(void (*action)(float));
		/*|*/ void set_animation_speed(float speed);
		/*|*/ void set_gamma_correction(bool enabled);
		/*|*/ void set_max_power(float volts, uint16_t milliamps);
		/*|*/ void set_frame_rate_target(uint16_t target);
		/*|*/ void set_line_wrap(bool enabled);
		/*|*/ void set_update_mode(t_update_mode mode, uint16_t FPS = 60);
		/*+---------------------------------------------------------------------------------*/ 
		
		/*+-- Functions - write() ----------------------------------------------------------*/ 
		/*|*/ void write(const uint8_t* icon, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ void write(uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ void write(char* message, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ void write(int16_t input, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ void write(uint16_t input, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ void write(int32_t input, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ void write(uint32_t input, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ #if defined(ESP8266) || defined(ESP32)
		/*|*/     void write(long unsigned int input, uint8_t x_pos = 0, uint8_t y_pos = 0); // pretty much the same as uint32_t, but Arduino is stupid
		/*|*/ #endif
		/*|*/ void write(float input, uint8_t places = 2, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ void write(double input, uint8_t places = 2, uint8_t x_pos = 0, uint8_t y_pos = 0);
		/*|*/ 
		/*|*/ void write_pix(char* message, int16_t x_offset = 0, int16_t y_offset = 0);
		/*|*/ void write_pix(const uint8_t* icon, int16_t x_offset = 0, int16_t y_offset = 0);
		/*|*/ 
		/*|*/ void add_char(char c, int16_t x_pos, int16_t y_pos);
		/*|*/ void add_char(const uint8_t* icon, int16_t x_pos, int16_t y_pos);
		/*+---------------------------------------------------------------------------------*/ 

		/*+-- Functions - print() ----------------------------------------------------------*/ 
		/*|*/ void print(const uint8_t* icon);
		/*|*/ void print(uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5);
		/*|*/ void print(char* message);
		/*|*/ void print(int16_t input);
		/*|*/ void print(uint16_t input);
		/*|*/ void print(int32_t input);
		/*|*/ void print(uint32_t input);
		/*|*/ #if defined(ESP8266) || defined(ESP32)
		/*|*/     void print(long unsigned int input); // pretty much the same as uint32_t, but Arduino is stupid
		/*|*/ #endif
		/*|*/ void print(float input, uint8_t places = 2);
		/*|*/ void print(double input, uint8_t places = 2);
		/*+---------------------------------------------------------------------------------*/ 

		/*+-- Functions - println() --------------------------------------------------------*/ 	
		/*|*/ void println(const uint8_t* icon);
		/*|*/ void println(uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5);
		/*|*/ void println(char* message);
		/*|*/ void println(int16_t input);
		/*|*/ void println(uint16_t input);
		/*|*/ void println(int32_t input);
		/*|*/ void println(uint32_t input);
		/*|*/ #if defined(ESP8266) || defined(ESP32)
		/*|*/     void println(long unsigned int input); // pretty much the same as uint32_t, but Arduino is stupid
		/*|*/ #endif
		/*|*/ void println(float input, uint8_t places = 2);
		/*|*/ void println(double input, uint8_t places = 2);
		/*+---------------------------------------------------------------------------------*/

		/*+-- Functions - Cursor -----------------------------------------------------------*/ 
		/*|*/ void    set_cursor(uint8_t x_position, uint8_t y_position = 0);
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
		/*|*/ void color(CRGB col); // Set all displays
		/*|*/ void color(CRGB col, uint8_t x, uint8_t y); // Set one display
		/*|*/ void color(CRGB col, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2); // Set a 2D rectangle
		/*|*/ CRGB kelvin_to_rgb(uint16_t temperature); // Get an approximate CRGB (not yet gamma corrected) of a blackbody radiation temperature
		/*+---------------------------------------------------------------------------------*/

		/*+-- Functions - Mask Effects -----------------------------------------------------*/ 
		/*|*/ void dim(uint8_t amount, bool reset_cursor = false); // Fade towards black by amount
		/*|*/ void blur(fract8 blur_amount);
		/*|*/ void blur_x(fract8 blur_amount);
		/*|*/ void blur_y(fract8 blur_amount);
		/*+---------------------------------------------------------------------------------*/
		
		/*+-- Functions - Color Effects ----------------------------------------------------*/ 
		/*|*/ void color_dim(uint8_t amount); // Fade towards black by amount
		/*|*/ void color_blur(fract8 blur_amount);
		/*|*/ void color_blur_x(fract8 blur_amount);
		/*|*/ void color_blur_y(fract8 blur_amount);
		/*+---------------------------------------------------------------------------------*/

		/*+-- Functions - 2D Tools ---------------------------------------------------------*/ 
		/*|*/ uint16_t xy(int16_t x, int16_t y, bool wrap = false);
		/*|*/ void     draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
		/*|*/ void     print_xy_map();
		/*+---------------------------------------------------------------------------------*/

		// Variables -------------------------------------------------------------------------

		CRGB *leds;
		CRGB *leds_out;
		
		uint8_t *mask;
		uint8_t *mask_out;		
		
		int16_t *xy_table;

		uint16_t matrix_width = 0;
		uint16_t matrix_height = 0;

		uint16_t NUM_LEDS = 0;
		uint16_t NUM_VISIBLE_LEDS = 0;
		
		volatile int16_t cursor_x = 0;
		volatile int16_t cursor_y = 0;
		
		CRGBPalette16 current_palette;		

		float frame_rate = 0.0;
		uint32_t t_last = 0;
		float delta = 1.0;

		float animation_speed = 1.0;
		
		
	private:
		// Functions ----------------------------------
		void build_controller(const uint8_t pin);
		void calc_xy();
		
		// Variables ----------------------------------
		Ticker animate;
		
		bool correct_gamma = false;
		uint8_t brightness_level = 255;
		
		uint8_t  pixie_pin = 0;
		float    max_V  = 5;
		uint16_t max_mA = 800;

		const uint8_t display_width  = 7;
		const uint8_t display_height = 11;

		uint8_t chars_x = 0;
		uint8_t chars_y = 0;

		const uint8_t bit_table[2] = {0,255};
		
		bool freeze = false;
		bool ticker_running = false;

		float fps_target = 60;
		
		bool line_wrap = false;
};

#endif
