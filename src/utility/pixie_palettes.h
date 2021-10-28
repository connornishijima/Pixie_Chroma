/*!
 * @file pixie_palettes.h
 *
 * Contains pre-defined color palettes for use with Pixie Chroma
 *
 * Last Updated by Connor Nishijima on 10/21/21
 */

#ifndef pixie_palettes_h
#define pixie_palettes_h

#include "Arduino.h"

const uint8_t RED_SOLID[] = {
	0,    255,   0,   0,
	255,  255,   0,	  0,
};

const uint8_t YELLOW_SOLID[] = {
	0,	255,	255,	0,
	255,	255,	255,	0,
};

const uint8_t GREEN_SOLID[] = {
	0,	0,	255,	0,
	255,	0,	255,	0,
};

const uint8_t CYAN_SOLID[] = {
	0,	0,	255,	255,
	255,	0,	255,	255,
};

const uint8_t BLUE_SOLID[] = {
	0,	255,	0,	0,
	255,	255,	0,	0,
};

const uint8_t PURPLE_SOLID[] = {
	0,	127,	0,	255,
	255,	127,	0,	255,
};

const uint8_t MAGENTA_SOLID[] = {
	0,	255,	0,	255,
	255,	255,	0,	255,
};

const uint8_t RAINBOW[] = {
	0,	255,	0,	0,
	17,	213,	42,	0,
	34,	171,	85,	0,
	51,	171,	127,	0,
	68,	171,	171,	0,
	85,	86,	213,	0,
	102,	0,	255,	0,
	119,	0,	213,	42,
	136,	0,	171,	85,
	153,	0,	86,	170,
	170,	0,	0,	255,
	187,	42,	0,	213,
	204,	85,	0,	171,
	221,	127,	0,	129,
	238,	171,	0,	85,
	255,	213,	0,	43
};

const uint8_t GRADIENT_RED_BLACK[] = {
	0,	255,	0,	0,
	255,	0,	0,	0,
};

const uint8_t GRADIENT_BLACK_RED_BLACK[] = {
	0,	0,	0,	0,
	127,	255,	0,	0,
	255,	0,	0,	0,
};

const uint8_t GRADIENT_GREEN_BLACK[] = {
	0,	0,	255,	0,
	255,	0,	0,	0,
};

const uint8_t GRADIENT_BLACK_GREEN_BLACK[] = {
	0,	0,	0,	0,
	127,	0,	255,	0,
	255,	0,	0,	0,
};

const uint8_t GRADIENT_BLUE_BLACK[] = {
	0,	0,	0,	255,
	255,	0,	0,	0,
};

const uint8_t GRADIENT_BLACK_BLUE_BLACK[] = {
	0,	0,	0,	0,
	127,	0,	0,	255,
	255,	0,	0,	0,
};

#endif
