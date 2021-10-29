/*!
 * @file pixie_animations.cpp
 *
 * Designed specifically to work with Pixie Chroma:
 * ----> https://connornishijima.github.io/PixieChroma
 *
 * Last Updated by Connor Nishijima on 10/21/21
 */

#include "pixie_animations.h"

void ANIMATION_NULL(float delta){
	// It does nothing, but it does nothing REALLY WELL! You can enable this
	// empty function with pix.set_animation(ANIMATION_NULL) to manually control color when you want
}

void ANIMATION_STATIC(float delta){
	extern PixieChroma pix;

	for(uint16_t x = 0; x < pix.matrix_width; x++){
		float progress = float(x / float(pix.matrix_width+4));
		CRGB col = ColorFromPalette(pix.current_palette, progress*255);
		for(uint16_t y = 0; y < pix.matrix_height; y++){
			uint16_t index = pix.xy(x,y);			
			pix.leds[index] = col;
		}
	}
}

void ANIMATION_PALETTE_SHIFT(int8_t amount, float delta){
	extern PixieChroma pix;
	static float iter = 0;

	for(uint16_t x = 0; x < pix.matrix_width; x++){
		float progress = float(x / float(pix.matrix_width+4));
		CRGB col = ColorFromPalette(pix.current_palette, progress*255+iter);
		for(uint16_t y = 0; y < pix.matrix_height; y++){
			uint16_t index = pix.xy(x,y);
			pix.leds[index] = col;
		}
	}

	iter += amount * pix.animation_speed * delta;
}

void ANIMATION_PALETTE_SHIFT_LEFT(float delta){
	ANIMATION_PALETTE_SHIFT(4, delta);
}

void ANIMATION_PALETTE_SHIFT_RIGHT(float delta){
	ANIMATION_PALETTE_SHIFT(-4, delta);
}

void ANIMATION_GLITTER(float delta){
	extern PixieChroma pix;
	pix.color_dim(16); // Fade to black by 6.25%;

	for(uint16_t x = 0; x < pix.matrix_width; x++){
		float progress = float(x / float(pix.matrix_width+4));
		for(uint16_t y = 0; y < pix.matrix_height; y++){
			if(random8() <= 32){ // 12.5% chance
				uint16_t index = pix.xy(x,y);
				CRGB col = ColorFromPalette(pix.current_palette, progress*255);
				pix.leds[index] = col;
			}
		}
	}
}

void _PENDULUM(float iter, float width){
	extern PixieChroma pix;		
	iter *= width;
	
	for(uint16_t x = 0; x < pix.matrix_width; x++){
		float progress = float(x / float(pix.matrix_width+4));
		float palette_index = (progress*255)+iter;
		
		if(palette_index < 0){
			palette_index = 0;
		}
		else if(palette_index > 255){ 
			palette_index = 255;
		}
		
		CRGB col = ColorFromPalette(pix.current_palette, uint8_t(palette_index));		
		for(uint16_t y = 0; y < pix.matrix_height; y++){
			uint16_t index = pix.xy(x,y);			
			pix.leds[index] = col;
		}
	}
}

void ANIMATION_PENDULUM(float delta){
	float iter = (beatsin8(60)-128);
	_PENDULUM(iter,0.5);
}

void ANIMATION_PENDULUM_WIDE(float delta){
	float iter = (beatsin8(60)-128);
	_PENDULUM(iter,1.0);
}

CRGBPalette16 make_gradient(CRGB col1, CRGB col2){
	const uint8_t gradient[] = {
		0,    col1.r, col1.g, col1.b,
		255,  col2.r, col2.g, col2.b
	};
	CRGBPalette16 pal;
	pal.loadDynamicGradientPalette(gradient);
	
	return pal;
}

CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3){
	const uint8_t gradient[] = {
		0,    col1.r, col1.g, col1.b,
		127,  col2.r, col2.g, col2.b,
		255,  col3.r, col3.g, col3.b
	};
	CRGBPalette16 pal;
	pal.loadDynamicGradientPalette(gradient);
	
	return pal;
}

CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4){
	const uint8_t gradient[] = {
		0,    col1.r, col1.g, col1.b,
		85,   col2.r, col2.g, col2.b,
		170,  col3.r, col3.g, col3.b,
		255,  col4.r, col4.g, col4.b
	};
	CRGBPalette16 pal;
	pal.loadDynamicGradientPalette(gradient);
	
	return pal;
}

CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5){
	const uint8_t gradient[] = {
		0,    col1.r, col1.g, col1.b,
		63,   col2.r, col2.g, col2.b,
		127,  col3.r, col3.g, col3.b,
		191,  col4.r, col4.g, col4.b,
		255,  col5.r, col5.g, col5.b
	};
	CRGBPalette16 pal;
	pal.loadDynamicGradientPalette(gradient);
	
	return pal;
}

CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6){
	const uint8_t gradient[] = {
		0,    col1.r, col1.g, col1.b,
		51,   col2.r, col2.g, col2.b,
		102,  col3.r, col3.g, col3.b,
		153,  col4.r, col4.g, col4.b,
		204,  col5.r, col5.g, col5.b,
		255,  col6.r, col6.g, col6.b
	};
	CRGBPalette16 pal;
	pal.loadDynamicGradientPalette(gradient);
	
	return pal;
}

CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7){
	const uint8_t gradient[] = {
		0,    col1.r, col1.g, col1.b,
		42,   col2.r, col2.g, col2.b,
		84,   col3.r, col3.g, col3.b,
		126,  col4.r, col4.g, col4.b,
		168,  col5.r, col5.g, col5.b,
		210,  col6.r, col6.g, col6.b,
		255,  col7.r, col7.g, col7.b
	};
	CRGBPalette16 pal;
	pal.loadDynamicGradientPalette(gradient);
	
	return pal;
}

CRGBPalette16 make_gradient(CRGB col1, CRGB col2, CRGB col3, CRGB col4, CRGB col5, CRGB col6, CRGB col7, CRGB col8){
	const uint8_t gradient[] = {
		0,    col1.r, col1.g, col1.b,
		36,   col2.r, col2.g, col2.b,
		72,   col3.r, col3.g, col3.b,
		108,  col4.r, col4.g, col4.b,
		144,  col5.r, col5.g, col5.b,
		180,  col6.r, col6.g, col6.b,
		216,  col7.r, col7.g, col7.b,
		255,  col8.r, col8.g, col8.b
	};
	CRGBPalette16 pal;
	pal.loadDynamicGradientPalette(gradient);
	
	return pal;
}
