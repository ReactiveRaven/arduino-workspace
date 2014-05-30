#include "Lcars.h"
#include "LcarsLed.h"
#include "LcarsDisplay.h"

LcarsLed::LcarsLed(
	Adafruit_ILI9340* tft,
	uint8_t pin,
	uint16_t color,
	uint16_t x,
	uint16_t y, 
	uint8_t width,
	uint8_t height
) {
	_tft = tft;
	_pin = pin;
	_color = color;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

void LcarsLed::on() {
	if (!_on) {
		if (_pin != 0) {
			digitalWrite(_pin, HIGH);
		} else {
			(*_tft).fillRect(_x, _y, _width, _height, _color);
		}
		_on = true;
	}
}

void LcarsLed::off() {
	if (_on) {
		if (_pin != 0) {
			digitalWrite(_pin, LOW);
		} else {
			(*_tft).fillRect(_x, _y, _width, _height, Lcars_Color_Black);
		}
		_on = false;
	}
}