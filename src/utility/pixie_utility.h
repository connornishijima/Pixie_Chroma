/*!
 * @file pixie_utility.h
 *
 * Contains utility arrays/functions for internal use, such as the gamma correction LUT. 
 *
 * Last Updated by Connor Nishijima on 4/14/22
 */

#ifndef pixie_utility_h
#define pixie_utility_h

// Extra utilities for PixieChroma code, such as the gamma LUT

#if defined(ARDUINO_ARCH_ESP32)
	#define ANALOG_PIN 35
#endif

/*! @brief  Used to store the pointer to any preset/custom animation functions the library needs to call during show(); */
void (*anim_func)(PixieChroma* _p, float delta);

/*! @brief  Used as a template by calc_xy() to build the XY coordinate map for accessing 1D LEDS in a 2D context. */
const int8_t xy_template[77] PROGMEM = {  
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

/*! @brief  Used as a fast lookup table for gamma correction. */
const uint8_t gamma8[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9,  10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99, 101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
	215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

/*!
@brief
Homebrew C function to convert double precision floats to char*. ([Arduino Forum link](https://forum.arduino.cc/t/ftoa/63464))
@param   input      Double value to convert
@param   buffer     char* to store resulting string in
@param   precision  How many places after the decimal point will be converted
@return  A char array equivalent of the input double
*/
char* dtoa(double input, char* buffer, int precision) {
	int32_t whole_part = (int32_t) input;

	// Deposit the whole part of the number.
	itoa( whole_part, buffer, 10 );

	// Now work on the faction if we need one.
	if( precision > 0 ) {

		// We do, so locate the end of the string and insert
		// a decimal point.
		char* end_of_string = buffer;
		while( *end_of_string != '\0' ){
			end_of_string++;
        }
		*end_of_string++ = '.'; 

		// Now work on the fraction, being sure to turn any negative
		// values positive.
		if (input < 0) {
			input *= -1;
			whole_part *= -1;
		}
		
		double fraction = input - whole_part;
		while (precision > 0) {
			// Multiply by ten and pull out the digit.
			fraction *= 10;
			whole_part = (int32_t) fraction;
			*end_of_string++ = '0' + whole_part;

			// Update the fraction and move on to the
			// next digit.
			fraction -= whole_part;
			precision--;
		}

		// Terminate the string.
		*end_of_string = '\0';
	}
	
    return buffer;
}

#endif
