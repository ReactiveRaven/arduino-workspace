#include "Lcars.h"
#include "Adafruit_ILI9340.h";
#include <boost/algorithm/string.hpp>
#include <string>

LcarsDisplay::LcarsDisplay(
	Lcars* lcars,
	Adafruit_ILI9340* tft,
	uint16_t color,
	uint16_t x,
	uint16_t y, 
	uint16_t width,
	uint16_t height,
	uint8_t corner,
	char *name
) {
	_lcars = lcars;
	_tft = tft;
	_color = color;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_corner = corner;

	top = (*_lcars).isTop(corner);
	left = (*_lcars).isLeft(corner);

	_ix = x + Lcars_B_Padding + (left ? Lcars_B_Width : 0);
	_iy = y + Lcars_B_Padding + (top ? Lcars_Bar_Height : 0);

	_iwidth = _width - Lcars_B_Padding2 - Lcars_B_Width;
	_iheight = _height - Lcars_B_Padding2 - Lcars_Bar_Height;

	setName(name);
}

void LcarsDisplay::begin() {
	render();
}

	inline void strtoupper(char* str)
	{
	    while (*str)
	    {
	        *str = toupper(*str);
	        str++;
	    }
	}

void LcarsDisplay::setName(char *name) {

	strtoupper(name);

	strcpy(_name, name);

	_namewidth = strlen(_name) * 6 - 1;
}

const char* LcarsDisplay::getName() {
	return _name;
}

void LcarsDisplay::setMode(uint8_t mode) {
	_mode = mode;
}

void LcarsDisplay::setColor(uint16_t color) {
	_color = color;

	renderShoulder();
}

void LcarsDisplay::renderShoulder() {
	(*_lcars).shoulder(
		_x, _y, _width, _height, _corner, _color
	);

	uint16_t cursorleft = _x + (left ? _width - _namewidth - Lcars_Bar_Height : Lcars_Bar_Height);

	(*_tft).fillRect(cursorleft - 2, _y, _namewidth + 4, 8, Lcars_Color_Black);
	(*_tft).setTextColor(_color);
	(*_tft).setCursor(
		cursorleft,
		_y
	);
	(*_lcars).log(_name);
	(*_tft).setTextColor(Lcars_Color_White);
}

void LcarsDisplay::render() {
	renderShoulder();
	(*_lcars).grid(
		_ix, _iy, _iwidth, _iheight, 10, 10, 0, 0, Lcars_Color_Brown_Dark
	);
	(*_lcars).grid(
		_ix, _iy, _iwidth, _iheight, 50, 50, 0, 0, _color
	);
}

void LcarsDisplay::clear() {
	(*_tft).fillRect(_ix, _iy, _iwidth, _iheight, Lcars_Color_Black);
}

void LcarsDisplay::CLEAR() {
	(*_tft).fillRect(_x, _y, _width, _height, Lcars_Color_Black);
}

void LcarsDisplay::setCorner(uint8_t corner) {
	_corner = corner;

	top = (*_lcars).isTop(corner);
	left = (*_lcars).isLeft(corner);
}