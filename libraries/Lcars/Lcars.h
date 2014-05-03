#ifndef _Lcars_
#define _Lcars_

#include <Adafruit_GFX.h>;
#include "Adafruit_ILI9340.h";
#include <Interruptions.h>;

class Lcars {
	public:
		Lcars(Adafruit_ILI9340* tft);

		void 
			begin(void),
			setMode(uint8_t mode);
	private:
		void render(void),
		     log(char msg),
		     shoulder(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t corner, uint16_t color);
		Adafruit_ILI9340* _tft;
		Interruptions _interruptions;
		uint8_t _mode;
		int16_t _width, _height;
};


#endif