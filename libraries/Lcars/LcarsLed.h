#ifndef _Lcars_Led_
#define _Lcars_Led_

#include "Adafruit_ILI9340.h";

class LcarsLed {
	public:
		LcarsLed() {};
		LcarsLed(
			Adafruit_ILI9340* tft, 
			uint8_t pin,
			uint16_t color,
			uint16_t x,
			uint16_t y, 
			uint8_t width,
			uint8_t height
		);


		void 
			on(void),
			off(void);

		void setTft(Adafruit_ILI9340* tft) { _tft = tft; };
		void setColor(uint16_t color) { _color = color; };
		void setX(uint16_t x) { _x = x; };
		void setY(uint16_t y) { _y = y; };
		void setWidth(uint16_t width) { _width = width; };
		void setHeight(uint16_t height) { _height = height; };
		void setPin(uint8_t pin) { _pin = pin; };

	private:
		Adafruit_ILI9340* _tft;
		uint8_t _pin, _width, _height;
		uint16_t _color, _x, _y;
		bool _on;
};

#endif