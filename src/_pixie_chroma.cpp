#include "PixieChroma.h"
#include "utility/_pixie_utility.h"

// -- GLOBALS -------------------------------------------------------------------------------------

volatile bool updated_too_soon = false;   // Used to prevent calling show() in the ISR before a previous show() finishes
const int8_t xy_template[77] PROGMEM = {  // Used as a template by calc_xy() to build the XY coordinate map for accessing 1D LEDS in a 2D context
	-2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2,
	-2, -1, -1, -1, -1, -1, -2,  
	-2, -1, -1, -1, -1, -1, -2,  
	-2, -1, -1, -1, -1, -1, -2,  
	-2, -1, -1, -1, -1, -1, -2,  
	-2, -1, -1, -1, -1, -1, -2,  
	-2, -1, -1, -1, -1, -1, -2,  
	-2, -1, -1, -1, -1, -1, -2,
	-2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2
};

// ---------------------------------------------------------------------------------------------------------|
// -- PUBLIC FUNCTIONS -------------------------------------------------------------------------------------|
// ---------------------------------------------------------------------------------------------------------|

/**************************************************************************/
/*!
    @brief  Used to initialize the PixieChroma library. Example usage before
            setup() would be:
	
				#include "PixieChroma.h"
                PixieChroma pix;
	
            NOTE: Due to current limitations with the library, your class
            instance MUST be named "pix". Mutiple instances are not yet
            possible. Because each of these functions are wrapped in the
            PixieChroma class, you'll use them like this:
	
                pix.print("Hello!");
	
*/
/**************************************************************************/
PixieChroma::PixieChroma(){}

/**************************************************************************/
/*!
    @brief  Initializes the display buffer, populates the XY coordinate
            table, defaults the display colors to green, loads the default
            CRGBPalette, initializes FastLED, sets the default power budget,
            and kicks off the animation ISR.
	
    @param  data_pin GPIO pin to use for FastLED output
    @param  pixies_x Number of Pixie PCBs in the X axis of your display
    @param  pixies_y Number of Pixie PCBs in the Y axis of your display
*/
/**************************************************************************/
void PixieChroma::begin(const uint8_t data_pin, uint8_t pixies_x, uint8_t pixies_y){
	pixie_pin = data_pin;

	chars_x = pixies_x*2; // Pixies have two chars each
	chars_y = pixies_y;

	matrix_width  = display_width*chars_x;
	matrix_height = display_height*chars_y;

	NUM_LEDS = (matrix_width*matrix_height);

	leds = new CRGB[NUM_LEDS+1]; // Hidden extra LED to write to if we call an out-of-bounds XY coordinate for color or mask
	mask = new uint8_t[NUM_LEDS+1];
	xy_table = new int16_t[NUM_LEDS];

	calc_xy();

	mask_out = new uint8_t[NUM_VISIBLE_LEDS];
	leds_out = new CRGB[NUM_VISIBLE_LEDS];

	for(uint16_t i = 0; i < NUM_VISIBLE_LEDS; i++){
		leds[i] = CRGB(0,255,0);
	}

	current_palette.loadDynamicGradientPalette(GREEN_SOLID);

	build_controller(pixie_pin); // ------ Initialize FastLED
	set_animation(ANIMATION_NULL); // ---- Set animation function to an empty one
	clear(); // -------------------------- Clear anything in mask (should be empty anyways), reset cursor
	set_max_power(5, 500); // ------------ Set default power budget in V and mA
	start_animation(); // ---------------- Kick off animation ISR
	
	
	Serial.println(NUM_LEDS);
	Serial.println(NUM_VISIBLE_LEDS);
	Serial.println(data_pin);
}

/**************************************************************************/
/*!
    @brief  Takes an 8-bit brightness value and passes it to FastLED
            internally, to provide global brightness control with temporal
            dithering
	
    @param  level 8-bit global brightness value (0-255)
*/
/**************************************************************************/
void PixieChroma::set_brightness(uint8_t level){
	brightness_level = level;
}

/**************************************************************************/
/*!
    @brief  Configures the update mode Pixie Chroma will use:
	
                set_update_mode(AUTOMATIC);

                    Refresh LEDs with new mask data on every ISR call (60FPS) 
				
                set_update_mode(HOLD_FOR_UPDATE);

                    Only refresh LEDs with new mask_data when pix.update() is
                    called, useful for preventing updates to the image before
                    its text is fully constructed. The animation ISR driving 
                    the color map will still update at 60FPS, regardless of
                    how often pix.update() is called.
				
    @param  update_type (AUTOMATIC or HOLD_FOR_UPDATE)
*/
/**************************************************************************/
void PixieChroma::set_update_mode(update_type t){
	_update_mode = t;
}

/**************************************************************************/
/*!
    @brief  Accepts a const uint8_t (8-bit) array with the following format
            to generate a FastLED Gradient Palette at runtime:

            const uint8_t* my_gradient_palette[] = {
            //  INDEX,	R_VAL,	G_VAL,	B_VAL,

			    0,      255,    0,      0, 
                127,    0,      255,    0, 
                255,    0,      0,      255, 
            };

            On each line is the index of the color (0-255) to express the
            position in the gradient this color occurs. So in the given
            example, it is a gradient from red at 0, to green at 127, to
            blue at 255.
				
    @param  pal FastLED "Gradient Palette" array
*/
/**************************************************************************/
void PixieChroma::set_palette(const uint8_t* pal){ // GRADIENT PALETTE
	current_palette.loadDynamicGradientPalette(pal);
}

/**************************************************************************/
/*!
    @brief  Accepts a FastLED CRGBPalette16 object to set the current color
            palette for animation
	
    @param  pal FastLED CRGBPalette16 object to use
*/
/**************************************************************************/
void PixieChroma::set_palette(CRGBPalette16 pal){ // STANDARD PALETTE
	current_palette = pal;
}

/**************************************************************************/
/*!
    @brief	Accepts a preset or custom function to use for the animation ISR.
            For a list of predefined animations, see _pixie_animations.h

    @param  action Function to set as an animation ISR
*/
/**************************************************************************/
void PixieChroma::set_animation(void (*action)()) {
	anim_func = action;
}

/**************************************************************************/
/*!
    @brief  Used to scale the animation speed of animation ISRs that can use
            pix.animation_speed to scale their speeds or for other effects
				
    @param  speed Floating point value: 1.0 = 100%, 3.2 = 320%, 0.5 = 50%
*/
/**************************************************************************/
void PixieChroma::set_animation_speed(float speed){
	animation_speed = speed;
}

/**************************************************************************/
/*!
    @brief  Allows you to enable built-in automatic gamma correction, using
            a fast LUT in _pixie_utility.h. (Not enabled by default)

    @param  enabled Whether or not to apply gamma correction
*/
/**************************************************************************/
void PixieChroma::set_gamma_correction(bool enabled){
	correct_gamma = enabled;
}

/**************************************************************************/
/*!
    @brief  Sets the cursor position in a 2D context, in whole displays.
            Wherever the cursor is, is where the next call to print() or
            write() will originate. Position is counted from zero. Remember,
            each Pixie Chroma has two "displays" on it.

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

                set_cursor(1,0)

                    Sets the cursor to the second display in the first row

                set_cursor(3,1)

                    Sets the cursor to the fourth display in the second row

    @param  x_position New cursor position on the X-axis, in whole displays
    @param  y_position New cursor position on the Y-axis, in whole displays
*/
/**************************************************************************/
void PixieChroma::set_cursor(uint8_t x_position, uint8_t y_position){
	cursor_x = (display_width*x)+1;
	cursor_y = (display_height*y)+2;
}

/**************************************************************************/
/*!
    @brief  Sets the maximum power budget in volts and milliamps. Knowing
            the average power consumption of these LEDs at any given color,
            FastLED will automatically globally scale down the output values
            with temporal dithering to lower power usage until it is within
            the budget defined here. Defaults to 5V / 500mA to protect PC
			USB ports if the LEDs are not independently powered.
			(2000mA = 2A, 500mA = 0.5A, etc.)

    @param  volts Total LED power budget in volts. (default: 5)
    @param  milliamps Total LED power budget in milliamps (default 500)
*/
/**************************************************************************/
void PixieChroma::set_max_power(float volts, uint16_t milliamps){
	max_V = V;
	max_mA = mA;
}

void PixieChroma::write(const uint8_t* icon, uint8_t x_pos, uint8_t y_pos){
	uint16_t x_start = 1;
	uint16_t y_start = 2;
	write_pix(icon, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
}

void PixieChroma::write(uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5, uint8_t x_pos, uint8_t y_pos){
	uint8_t icon[5] = {icon_col_1,icon_col_2,icon_col_3,icon_col_4,icon_col_5};
	write(icon, x_pos, y_pos);
}


void PixieChroma::write(char* message, uint8_t x_pos, uint8_t y_pos){
	uint16_t x_start = 1;
	uint16_t y_start = 2;
	write_pix(message, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
}

void PixieChroma::write(int16_t input, uint8_t x_pos, uint8_t y_pos){
	uint16_t x_start = 1;
	uint16_t y_start = 2;

	char char_buf[32];
	itoa(input,char_buf,10);

	write_pix(char_buf, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
}

void PixieChroma::write(uint16_t input, uint8_t x_pos, uint8_t y_pos){
	uint16_t x_start = 1;
	uint16_t y_start = 2;

	char char_buf[32];
	utoa(input,char_buf,10);

	write_pix(char_buf, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
}

void PixieChroma::write(int32_t input, uint8_t x_pos, uint8_t y_pos){
	uint16_t x_start = 1;
	uint16_t y_start = 2;

	char char_buf[32];
	ltoa(input,char_buf,10);

	write_pix(char_buf, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
}

void PixieChroma::write(uint32_t input, uint8_t x_pos, uint8_t y_pos){
	uint16_t x_start = 1;
	uint16_t y_start = 2;

	char char_buf[32];
	ultoa(input,char_buf,10);

	write_pix(char_buf, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
}

#if defined(ESP8266) || defined(ESP32)
	void PixieChroma::write(long unsigned int input, uint8_t x_pos, uint8_t y_pos){
		uint16_t x_start = 1;
		uint16_t y_start = 2;

		char char_buf[32];
		ultoa(input,char_buf,10);

		write_pix(char_buf, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
	}
#endif

void PixieChroma::write(double input, uint8_t places, uint8_t x_pos, uint8_t y_pos){
	uint16_t x_start = 1;
	uint16_t y_start = 2;

	char char_buf[32];
	dtoa(input,char_buf,places);

	write_pix(char_buf, x_start+(display_width*x_pos), y_start+(display_height*y_pos));
}

void PixieChroma::write(float input, uint8_t places, uint8_t x_pos, uint8_t y_pos){
	write(double(input), places, x_pos, y_pos);
}

void PixieChroma::write_pix(const uint8_t* icon, int16_t x_pos, int16_t y_pos){
	freeze = true;
	int16_t x_offset = x_pos;
	int16_t y_offset = y_pos;
	add_char(icon, cursor_x, cursor_y);
	cursor_x += display_width;
	freeze = false;
}

void PixieChroma::write_pix(char* message, int16_t x_pos, int16_t y_pos){
	freeze = true;
	uint8_t len = strlen(message);
	Serial.println(len);
	int16_t x_offset = x_pos;
	int16_t y_offset = y_pos;
	for(uint8_t i = 0; i < len; i++){
		if(message[i] == '\n'){
			y_offset += display_height;
			x_offset = 1;
			cursor_x = 1;
			cursor_y += display_height;
		}
		else if(message[i] == 0 || message[i] == '\0'){ // early end of string
			freeze = false;
			return;
		}
		else{
			add_char(message[i], cursor_x, cursor_y);
			x_offset += display_width;
			cursor_x += display_width;
		}		
	}

	freeze = false;
}

void PixieChroma::add_char(char chr, int16_t x_pos, int16_t y_pos){
	if (chr >= 32) {
		chr -= 32;
	}

	for(uint8_t x = 0; x < 5; x++){
		uint8_t column = pgm_read_byte(font+(chr * 5 + x));

		uint16_t row1_index = xy(x_pos+x, y_pos+0);
		uint16_t row2_index = xy(x_pos+x, y_pos+1);
		uint16_t row3_index = xy(x_pos+x, y_pos+2);
		uint16_t row4_index = xy(x_pos+x, y_pos+3);
		uint16_t row5_index = xy(x_pos+x, y_pos+4);
		uint16_t row6_index = xy(x_pos+x, y_pos+5);
		uint16_t row7_index = xy(x_pos+x, y_pos+6);

		// "Subtract" from mask transparency with saturating function
		mask[row1_index] = qadd8( mask[row1_index],  bit_table[bitRead(column,0)] );
		mask[row2_index] = qadd8( mask[row2_index],  bit_table[bitRead(column,1)] );
		mask[row3_index] = qadd8( mask[row3_index],  bit_table[bitRead(column,2)] );
		mask[row4_index] = qadd8( mask[row4_index],  bit_table[bitRead(column,3)] );
		mask[row5_index] = qadd8( mask[row5_index],  bit_table[bitRead(column,4)] );
		mask[row6_index] = qadd8( mask[row6_index],  bit_table[bitRead(column,5)] );
		mask[row7_index] = qadd8( mask[row7_index],  bit_table[bitRead(column,6)] );
	}
}

void PixieChroma::add_char(const uint8_t* icon, int16_t x_pos, int16_t y_pos){
	for(uint8_t x = 0; x < 5; x++){
		uint8_t column = pgm_read_byte_far(icon+x);

		uint16_t row1_index = xy(x_pos+x, y_pos+0);
		uint16_t row2_index = xy(x_pos+x, y_pos+1);
		uint16_t row3_index = xy(x_pos+x, y_pos+2);
		uint16_t row4_index = xy(x_pos+x, y_pos+3);
		uint16_t row5_index = xy(x_pos+x, y_pos+4);
		uint16_t row6_index = xy(x_pos+x, y_pos+5);
		uint16_t row7_index = xy(x_pos+x, y_pos+6);

		// "Subtract" from mask transparency with saturating function
		mask[row1_index] = qadd8( mask[row1_index],  bit_table[bitRead(column,0)] );
		mask[row2_index] = qadd8( mask[row2_index],  bit_table[bitRead(column,1)] );
		mask[row3_index] = qadd8( mask[row3_index],  bit_table[bitRead(column,2)] );
		mask[row4_index] = qadd8( mask[row4_index],  bit_table[bitRead(column,3)] );
		mask[row5_index] = qadd8( mask[row5_index],  bit_table[bitRead(column,4)] );
		mask[row6_index] = qadd8( mask[row6_index],  bit_table[bitRead(column,5)] );
		mask[row7_index] = qadd8( mask[row7_index],  bit_table[bitRead(column,6)] );
	}
}

void PixieChroma::print(const uint8_t* icon){
	write_pix(icon, cursor_x, cursor_y);
}

void PixieChroma::print(uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5){
	const uint8_t icon[5] = {
		icon_col_1,
		icon_col_2,
		icon_col_3,
		icon_col_4,
		icon_col_5,
	};
	write_pix(icon, cursor_x, cursor_y);
}

void PixieChroma::print(char* message){
	write_pix(message, cursor_x, cursor_y);
}

void PixieChroma::print(int16_t input){
	char char_buf[32];
	itoa(input,char_buf,10);
	write_pix(char_buf, cursor_x, cursor_y);
}

void PixieChroma::print(uint16_t input){
	char char_buf[32];
	utoa(input,char_buf,10);
	write_pix(char_buf, cursor_x, cursor_y);
}

void PixieChroma::print(int32_t input){
	char char_buf[32];
	ltoa(input,char_buf,10);
	write_pix(char_buf, cursor_x, cursor_y);
}

void PixieChroma::print(uint32_t input){
	char char_buf[32];
	ultoa(input,char_buf,10);
	write_pix(char_buf, cursor_x, cursor_y);
}

#if defined(ESP8266) || defined(ESP32)
	void PixieChroma::print(long unsigned int input){
		char char_buf[32];
		ultoa(input,char_buf,10);
		write_pix(char_buf, cursor_x, cursor_y);
	}
#endif

void PixieChroma::print(double input, uint8_t places){
	char char_buf[32];
	dtoa(input,char_buf,places);
	write_pix(char_buf, cursor_x, cursor_y);
}

void PixieChroma::print(float input, uint8_t places){
	print(double(input), places);
}

void PixieChroma::println(const uint8_t* icon){
	write_pix(icon, cursor_x, cursor_y); // ........ Output
	cursor_x = 1;
	cursor_y += display_height;
}

void PixieChroma::println(uint8_t icon_col_1, uint8_t icon_col_2, uint8_t icon_col_3, uint8_t icon_col_4, uint8_t icon_col_5){
	const uint8_t icon[5] = {
		icon_col_1,
		icon_col_2,
		icon_col_3,
		icon_col_4,
		icon_col_5,
	};
	write_pix(icon, cursor_x, cursor_y);
	cursor_x = 1;
	cursor_y += display_height;
}

void PixieChroma::println(char* message){
	write_pix(message, cursor_x, cursor_y); // ........ Output
	cursor_x = 1;
	cursor_y += display_height;
}

void PixieChroma::println(int16_t input){
	char char_buf[32];
	itoa(input,char_buf,10);
	println(char_buf);
}

void PixieChroma::println(uint16_t input){
	char char_buf[32];
	utoa(input,char_buf,10);
	println(char_buf);
}

void PixieChroma::println(int32_t input){
	char char_buf[32];
	ltoa(input,char_buf,10);
	println(char_buf);
}

void PixieChroma::println(uint32_t input){
	char char_buf[32];
	ultoa(input,char_buf,10);
	println(char_buf);
}

#if defined(ESP8266) || defined(ESP32)
	void PixieChroma::println(long unsigned int input){
		char char_buf[32];
		ultoa(input,char_buf,10);
		println(char_buf);
	}
#endif

void PixieChroma::println(double input, uint8_t places){
	char char_buf[32];
	dtoa(input,char_buf,places);
	println(char_buf);
}

void PixieChroma::println(float input, uint8_t places){
	println(double(input), places);
}

void PixieChroma::blur(fract8 blur_amount){
	blur_x(blur_amount);
	blur_y(blur_amount);
}

void PixieChroma::blur_x(fract8 blur_amount){
	uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for( uint8_t row = 0; row < matrix_height; row++) {
        uint8_t carryover = 0;
        for( uint8_t i = 0; i < matrix_width; i++) {
            uint8_t cur = mask[xy(i,row)];
            uint8_t part = cur;
            part = scale8(part, seep);
            cur  = scale8(cur, keep);
            cur  = qadd8(cur,carryover);
            if(i){
				mask[xy(i-1,row)] = qadd8(mask[xy(i-1,row)],part);
			}
            mask[xy(i,row)] = cur;
            carryover = part;
        }
    }
}

void PixieChroma::blur_y(fract8 blur_amount){
	// blur columns
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for( uint8_t col = 0; col < matrix_width; ++col) {
        uint8_t carryover = 0;
        for( uint8_t i = 0; i < matrix_height; ++i) {			
			uint8_t cur = mask[xy(col,i)];
            uint8_t part = cur;
            part = scale8(part, seep);
            cur  = scale8(cur, keep);
            cur  = qadd8(cur,carryover);
            if(i){
				mask[xy(col,i-1)] = qadd8(mask[xy(col,i-1)],part);
			}
            mask[xy(col,i)] = cur;
            carryover = part;
        }
    }
}

void PixieChroma::dim(uint8_t amount, bool reset_cursor){
	if(reset_cursor){
		set_cursor(0,0);
	}
	freeze = true;
	
	for(uint16_t i = 0; i < NUM_LEDS; i+=11){
		mask[i+0]  = scale8(mask[i+0],  255-amount);
		mask[i+1]  = scale8(mask[i+1],  255-amount);
		mask[i+2]  = scale8(mask[i+2],  255-amount);
		mask[i+3]  = scale8(mask[i+3],  255-amount);
		mask[i+4]  = scale8(mask[i+4],  255-amount);
		mask[i+5]  = scale8(mask[i+5],  255-amount);
		mask[i+6]  = scale8(mask[i+6],  255-amount);
		mask[i+7]  = scale8(mask[i+7],  255-amount);
		mask[i+8]  = scale8(mask[i+8],  255-amount);
		mask[i+9]  = scale8(mask[i+9],  255-amount);
		mask[i+10] = scale8(mask[i+10], 255-amount);
	}
	freeze = false;
}

void PixieChroma::color_blur(fract8 blur_amount){
	color_blur_x(blur_amount);
	color_blur_y(blur_amount);
}

void PixieChroma::color_blur_x(fract8 blur_amount){
	uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for( uint8_t row = 0; row < matrix_height; row++) {
        uint8_t carryover = 0;
        for( uint8_t i = 0; i < matrix_width; i++) {
            CRGB cur = leds[xy(i,row)];
            CRGB part = cur;
            part.nscale8( seep);
            cur.nscale8( keep);
            cur += carryover;
            if( i) leds[xy(i-1,row)] += part;
            leds[xy(i,row)] = cur;
            carryover = part;
        }
    }
}

void PixieChroma::color_blur_y(fract8 blur_amount){
	// blur rows same as columns, for irregular matrix
    uint8_t keep = 255 - blur_amount;
    uint8_t seep = blur_amount >> 1;
    for( uint8_t row = 0; row < matrix_width; row++) {
        CRGB carryover = CRGB::Black;
        for( uint8_t i = 0; i < matrix_height; i++) {
            CRGB cur = leds[xy(i,row)];
            CRGB part = cur;
            part.nscale8( seep);
            cur.nscale8( keep);
            cur += carryover;
            if( i) leds[xy(i-1,row)] += part;
            leds[xy(i,row)] = cur;
            carryover = part;
        }
    }
}

void PixieChroma::color_dim(uint8_t amount){
	freeze = true;
	CRGBSet leds_temp(leds, NUM_LEDS);
	leds_temp.fadeToBlackBy(amount);
	freeze = false;
}

void PixieChroma::clear(){
	freeze = true;
	memset(mask, 0, NUM_LEDS);
	set_cursor(0,0);
	freeze = false;
}

void PixieChroma::update(){
	freeze = true;
	memcpy(mask_out, mask, NUM_VISIBLE_LEDS);
	freeze = false;
}

uint16_t PixieChroma::xy(int16_t x, int16_t y, bool wrap) {
	if(wrap){
		while(x < 0){
			x += matrix_width;
		}
		while(x >= matrix_width){
			x -= matrix_width;
		}
		while(y < 0){
			y += matrix_height;
		}
		while(y >= matrix_height){
			y -= matrix_height;
		}
	}
	else{
		if(x < 0){
			return NUM_LEDS; // If offscreen without wrap return last led in matrix
		}
		else if(x >= matrix_width){
			return NUM_LEDS; // If offscreen without wrap return last led in matrix
		}
		if(y < 0){
			return NUM_LEDS; // If offscreen without wrap return last led in matrix
		}
		else if(y >= matrix_height){
			return NUM_LEDS; // If offscreen without wrap return last led in matrix
		}
	}

	// done wrapping / culling, time for transformation
	return xy_table[ (y * matrix_width) + x ];
}

void PixieChroma::color(CRGB col){
	fill_solid(leds, NUM_LEDS, col);
}

void PixieChroma::color(CRGB col, uint8_t x, uint8_t y){
	int16_t x_pos = x*display_width+1;
	int16_t y_pos = y*display_height+2;
	
	for(uint8_t xi = 0; xi < 5; xi++){
		leds[xy(x_pos+xi, y_pos+0)] = col;
		leds[xy(x_pos+xi, y_pos+1)] = col;
		leds[xy(x_pos+xi, y_pos+2)] = col;
		leds[xy(x_pos+xi, y_pos+3)] = col;
		leds[xy(x_pos+xi, y_pos+4)] = col;
		leds[xy(x_pos+xi, y_pos+5)] = col;
		leds[xy(x_pos+xi, y_pos+6)] = col;
	}
}

void PixieChroma::color(CRGB col, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	if(x2 < x1 || y2 < y1){
		return;
	}

	// Make rectangle selection inclusive
	x2+=1;
	y2+=1;
	
	int16_t x1_pos = x1*display_width+1;
	int16_t y1_pos = y1*display_height+2;
	
	int16_t x2_pos = x2*display_width+1;
	int16_t y2_pos = y2*display_height+2;

	uint16_t x_delta = x2_pos-x1_pos;
	uint16_t y_delta = y2_pos-y1_pos;
	
	for(uint16_t y = 0; y < y_delta; y++){
		for(uint16_t x = 0; x < x_delta; x++){
			int16_t x2_pos = x1_pos+x;
			int16_t y2_pos = y1_pos+y;
			leds[xy(x2_pos, y2_pos)] = col;
		}
	}
}

void PixieChroma::draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2){
	//Bresenham's line algorithm
	uint16_t index;
	
	int16_t x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
	dx=x2-x1;
	dy=y2-y1;
	dx1=fabs(dx);
	dy1=fabs(dy);
	px=2*dy1-dx1;
	py=2*dx1-dy1;
	if(dy1<=dx1){
		if(dx>=0){
			x=x1;
			y=y1;
			xe=x2;
		}
		else{
			x=x2;
			y=y2;
			xe=x1;
		}
		index = xy(x,y);
		mask[index] = qadd8( 255, mask[index] );
		for(i=0;x<xe;i++){
			x=x+1;
			if(px<0){
				px=px+2*dy1;
			}
			else{
				if((dx<0 && dy<0) || (dx>0 && dy>0)){
					y=y+1;
				}
				else{
					y=y-1;
				}
				px=px+2*(dy1-dx1);
			}
			delay(0);
			index = xy(x,y);
			mask[index] = qadd8( 255, mask[index] );
		}
	}
	else{
		if(dy>=0){
			x=x1;
			y=y1;
			ye=y2;
		}
		else{
			x=x2;
			y=y2;
			ye=y1;
		}
		index = xy(x,y);
		mask[index] = qadd8( 255, mask[index] );
		for(i=0;y<ye;i++){
			y=y+1;
			if(py<=0){
				py=py+2*dx1;
			}
			else{
				if((dx<0 && dy<0) || (dx>0 && dy>0)){
					x=x+1;
				}
				else{
					x=x-1;
				}
				py=py+2*(dx1-dy1);
			}
			index = xy(x,y);
			mask[index] = qadd8( 255, mask[index] );
		}
	}
}

// Tanner Helland formula
CRGB PixieChroma::kelvin_to_rgb(uint16_t temperature){
	float    _temperature;
	float    _red;
	float    _green;
	float    _blue;

	_temperature = constrain(temperature, 0, 65500);

	_red = _green = _blue = 0;  
	float t = _temperature * 0.01;

	if (t <= 66){
		_red = 255;
		_green = (99.4708025861 * log(t)) - 161.1195681661;
		if (t > 19){
			_blue = (138.5177312231 * log(t - 10)) - 305.0447927307;
		}
		else{
			_blue = 0;
		}
	}
	else{
		_red   = 329.698727466  * pow(t - 60, -0.1332047592);
		_green = 288.1221695283 * pow(t - 60, -0.0755148492);
		_blue  = 255;
	}

	float f = 0.01 * 100;

	_red   = constrain(f * _red,   0, 255);
	_green = constrain(f * _green, 0, 255);
	_blue  = constrain(f * _blue,  0, 255);

	return CRGB(_red, _green, _blue);
}

void PixieChroma::show(){
	if(!updated_too_soon){ // Prevents show() if called before last one finished
		updated_too_soon = true;
		if(!freeze){ // Prevents show() if called while text or animation is still being rendered
			
			noInterrupts();
			if(_update_mode == AUTOMATIC){ // If we're not holding out for a pix.update() call, show with the current mask
				memcpy(mask_out, mask, NUM_VISIBLE_LEDS);
			}
			
			memcpy(leds_out, leds, sizeof(CRGB)*NUM_VISIBLE_LEDS);

			for(uint16_t i = 0; i < NUM_VISIBLE_LEDS; i+=7){ // NUM VISIBLE always a multiple of 7, this is a slight unrolling of the for loop to save on speed
				// MASKING
				leds_out[i+0].fadeLightBy( 255-mask_out[i+0] ); // Apply mask "over" LED color layer
				leds_out[i+1].fadeLightBy( 255-mask_out[i+1] );
				leds_out[i+2].fadeLightBy( 255-mask_out[i+2] );
				leds_out[i+3].fadeLightBy( 255-mask_out[i+3] );
				leds_out[i+4].fadeLightBy( 255-mask_out[i+4] );
				leds_out[i+5].fadeLightBy( 255-mask_out[i+5] );
				leds_out[i+6].fadeLightBy( 255-mask_out[i+6] );


				// GAMMA CORRECTION
				if(correct_gamma){					
					leds_out[i+0].r = gamma8[leds_out[i+0].r]; // Apply gamma correction LUT
					leds_out[i+0].g = gamma8[leds_out[i+0].g];
					leds_out[i+0].b = gamma8[leds_out[i+0].b];

					leds_out[i+1].r = gamma8[leds_out[i+1].r];
					leds_out[i+1].g = gamma8[leds_out[i+1].g];
					leds_out[i+1].b = gamma8[leds_out[i+1].b];

					leds_out[i+2].r = gamma8[leds_out[i+2].r];
					leds_out[i+2].g = gamma8[leds_out[i+2].g];
					leds_out[i+2].b = gamma8[leds_out[i+2].b];

					leds_out[i+3].r = gamma8[leds_out[i+3].r];
					leds_out[i+3].g = gamma8[leds_out[i+3].g];
					leds_out[i+3].b = gamma8[leds_out[i+3].b];

					leds_out[i+4].r = gamma8[leds_out[i+4].r];
					leds_out[i+4].g = gamma8[leds_out[i+4].g];
					leds_out[i+4].b = gamma8[leds_out[i+4].b];

					leds_out[i+5].r = gamma8[leds_out[i+5].r];
					leds_out[i+5].g = gamma8[leds_out[i+5].g];
					leds_out[i+5].b = gamma8[leds_out[i+5].b];

					leds_out[i+6].r = gamma8[leds_out[i+6].r];
					leds_out[i+6].g = gamma8[leds_out[i+6].g];
					leds_out[i+6].b = gamma8[leds_out[i+6].b];
				}
			}
			
			// Regulate brightness to keep power within budget set with pix.set_max_power(V, mA);
			FastLED.setBrightness(calculate_max_brightness_for_power_vmA(leds_out, NUM_VISIBLE_LEDS, brightness_level, max_V, max_mA));
			FastLED.show();

			interrupts();
		}
		updated_too_soon = false;
	}
	else{
		return;
	}
}

// -- PRIVATE FUNCTIONS -------------------------------------------------------------------------------------

void PixieChroma::build_controller(const uint8_t pin){
	// FastLED control pin has to be defined as a constant, (not just declared const, it's weirdly different) so
	// this is a hacky workaround. Since we have to hardwire the damn pin number variable, we also have
	// to be careful of the current architecture we're compiling to, since FastLED doesn't let you 
	// define non-existent pins either.
	
	#ifdef ESP8266
		if (pin == 0){FastLED.addLeds<WS2812B, 0, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 1){FastLED.addLeds<WS2812B, 1, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 2){FastLED.addLeds<WS2812B, 2, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 3){FastLED.addLeds<WS2812B, 3, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 4){FastLED.addLeds<WS2812B, 4, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 5){FastLED.addLeds<WS2812B, 5, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
			// annnnd a bunch of missing pins that are tied to external flash...
		if (pin == 12){FastLED.addLeds<WS2812B, 12, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 13){FastLED.addLeds<WS2812B, 13, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 14){FastLED.addLeds<WS2812B, 14, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 15){FastLED.addLeds<WS2812B, 15, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 16){FastLED.addLeds<WS2812B, 16, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
	#endif
	
	#ifdef ESP32
		if (pin == 0){FastLED.addLeds<WS2812B, 0, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 1){FastLED.addLeds<WS2812B, 1, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 2){FastLED.addLeds<WS2812B, 2, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 3){FastLED.addLeds<WS2812B, 3, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 4){FastLED.addLeds<WS2812B, 4, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 5){FastLED.addLeds<WS2812B, 5, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 12){FastLED.addLeds<WS2812B, 12, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 13){FastLED.addLeds<WS2812B, 13, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 14){FastLED.addLeds<WS2812B, 14, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 15){FastLED.addLeds<WS2812B, 15, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 16){FastLED.addLeds<WS2812B, 16, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 17){FastLED.addLeds<WS2812B, 17, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 18){FastLED.addLeds<WS2812B, 18, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 19){FastLED.addLeds<WS2812B, 19, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 21){FastLED.addLeds<WS2812B, 21, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 22){FastLED.addLeds<WS2812B, 22, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 23){FastLED.addLeds<WS2812B, 23, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 25){FastLED.addLeds<WS2812B, 25, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 26){FastLED.addLeds<WS2812B, 26, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 27){FastLED.addLeds<WS2812B, 27, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 32){FastLED.addLeds<WS2812B, 32, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 33){FastLED.addLeds<WS2812B, 33, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
	#endif
	
	#ifdef SAMD_SERIES
		if (pin == 0){FastLED.addLeds<WS2812B, 0, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 1){FastLED.addLeds<WS2812B, 1, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 2){FastLED.addLeds<WS2812B, 2, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 3){FastLED.addLeds<WS2812B, 3, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 4){FastLED.addLeds<WS2812B, 4, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 5){FastLED.addLeds<WS2812B, 5, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 6){FastLED.addLeds<WS2812B, 6, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 7){FastLED.addLeds<WS2812B, 7, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 8){FastLED.addLeds<WS2812B, 8, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 9){FastLED.addLeds<WS2812B, 9, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
		if (pin == 10){FastLED.addLeds<WS2812B, 10, GRB>(leds_out, NUM_VISIBLE_LEDS).setCorrection(TypicalLEDStrip);}
	#endif
}

void PixieChroma::start_animation(){
	timer1_attachInterrupt(ANIMATE);
	timer1_enable(TIM_DIV1, TIM_EDGE, TIM_SINGLE);
	timer1_write(1000000); // First frame 1,000,000 CPU cycles from now
}

void PixieChroma::calc_xy(){
  // Initialize XY table
	for(uint16_t yi = 0; yi < chars_y; yi++){
		for(uint16_t y = 0; y < 11; y++){
			for(uint16_t xi = 0; xi < chars_x; xi++){
				for(uint16_t x = 0; x < 7; x++){
					int16_t x_pos = (xi*display_width)+x;
					int16_t y_pos = (yi*display_height)+y;

					int16_t x_pos_mod = x_pos % display_width;
					int16_t y_pos_mod = y_pos % display_height;

					uint16_t i_table = (y_pos * matrix_width) + x_pos;
					uint16_t i_template = (y_pos_mod * display_width) + x_pos_mod;

					xy_table[i_table] = int8_t(pgm_read_byte(xy_template + i_template));
				}
			}
		}
	}

	Serial.println("SOLVING VISIBLE");

	// Initialize first row of displays
	uint8_t visible_rows = 0;
	for(uint16_t row = 0; row < display_height; row++){
		uint16_t index = (5*visible_rows);
		bool found_visible = false;
		int16_t last_data = 0;
		for(uint16_t col = 0; col < matrix_width; col++){
			uint16_t i = (row*matrix_width)+col;
			int16_t map_data = xy_table[i];

			if(map_data == -1){
				xy_table[i] = index;
				index++;
				found_visible = true;
			}

			else if(map_data == -2){
				if(last_data == -1){
					index+=30;
				}
			}

			last_data = map_data;
		}

		if(found_visible){
			visible_rows++;
		}
	}

	NUM_VISIBLE_LEDS = 35*chars_x; // account for first row

	// Solve additional rows
	if(chars_y > 1){
		uint8_t rows_left = chars_y-1;
		uint16_t row_length = (display_width*display_height)*chars_x;
		for(uint8_t ii = 0; ii < rows_left; ii++){
			for(uint16_t r = 0; r < row_length; r++){
				uint16_t final_src_index = (ii*row_length)+r;
				int16_t src_data = xy_table[final_src_index];
				if(src_data >= 0){
					src_data += (35*chars_x);

					if(src_data > NUM_VISIBLE_LEDS){
						NUM_VISIBLE_LEDS = src_data;
					}
					xy_table[final_src_index+row_length] = src_data;
				}
			}
		}
	}

	uint16_t index = NUM_VISIBLE_LEDS;
	Serial.println(NUM_VISIBLE_LEDS);
	Serial.println(NUM_LEDS);

	Serial.println("SOLVING INVISIBLE");
	for(uint16_t y = 0; y < matrix_height; y++){
		for(uint16_t x = 0; x < matrix_width; x++){
			uint16_t i = (y * matrix_width) + x;
			uint16_t j = xy_table[i];

			if(xy_table[i] == -2){
				xy_table[i] = index;
				index++;
			}
		}
	}
	Serial.println("DONE");

	for(uint16_t y = 0; y < matrix_height; y++){
		for(uint16_t x = 0; x < matrix_width; x++){
			uint16_t i = (y * matrix_width) + x;
			Serial.print(xy_table[i]);
			Serial.print('\t');
		}
		Serial.println();
	}
}

void PixieChroma::print_xy_map(){
	for(uint8_t y = 0; y < matrix_height; y++){
		for(uint8_t x = 0; x < matrix_width; x++){
			uint16_t index = (matrix_width*y)+x;
			Serial.print(xy_table[index]);
			Serial.print('\t');
		}
		Serial.println();
	}
}

#if defined(ARDUINO_ARCH_ESP8266) // TODO: NEED ESP32 SUPPORT
	void ICACHE_RAM_ATTR ANIMATE(){
		static const uint32_t frame_cycles = F_CPU / (F_CPU / 2666666); // 60 FPS, independent of ESP CPU frequency (this long division is only called once because of "static" declaration)
		timer1_write(frame_cycles); // Come back here in 1/60th second
		
		extern PixieChroma pix;
		// This is an imperfect solution, but extern-ing the class instance defined in the
		// user sketch, this ISR routine (which can't be in a class) can still access it.
		// _pixie_animations.cpp does this trick as well. This is why you cannot currently
		// name your PixieChroma class instance anything but "pix". :/
		//
		// The solution to this would be the ISR setting a flag that a pix.process() function would read, but
		// That would mean users can't ever delay() or use other blocking code for more than a split
		// second without having to call the "pix.process()" again to avoid choppy output.
		//
		// At the cost of some non-standard methods of accessing the class in here, beginners to Arduino
		// can just use simple print() and clear() methods to update the displays, while our
		// tricky ISR keeps animation running nicely, even with blocking code in the main loop.
		
		if(!pix.freeze){ // If not currently rendering to color or mask
			uint32_t t_now = micros(); // Get current time
			pix.frame_time = (t_now - pix.t_last);
			pix.t_last = t_now;
			
			anim_func(); // Call custom animation function
			pix.show();  // Update Pixie Chromas
		}
	}
#endif