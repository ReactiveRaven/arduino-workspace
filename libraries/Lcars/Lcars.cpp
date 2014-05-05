#include "Lcars.h"
#include <Adafruit_GFX.h>;
#include "Adafruit_ILI9340.h";
#include <Interruptions.h>;
#include "LcarsDisplay.h";
#include "LcarsDisplay.h";

Lcars::Lcars(Adafruit_ILI9340* tft)
{
	_tft = tft;
	_posRadius = Lcars_B_Width / 2;
	_negRadius = Lcars_B_Width / 4;
	_interruptions = Interruptions();
	begin();
}

void Lcars::begin() {
	(*_tft).setRotation(3);
  	(*_tft).fillScreen(Lcars_Color_Black);
  	_width = (*_tft).width();
  	_height = (*_tft).height() / 3 * 2;
  	_width3 = _width / 3;
  	_width32 = _width3 * 2;
  	setMode(1);
}

void Lcars::setMode(uint8_t mode) {
	_mode = mode;
	render();
}

void Lcars::log(const char* message) {
	(*_tft).println(message);
}

void Lcars::log(unsigned int n) {
	(*_tft).println(n, 10);
}

void Lcars::shoulder(
	uint16_t x, uint16_t y,
	uint16_t width, uint16_t height,
	uint8_t corner, uint16_t color
) {
	width = width - Lcars_B_VSpacing;
	height = height - Lcars_B_HSpacing;
	uint8_t top = isTop(corner);
	uint8_t left = isLeft(corner);

	// vertical
	(*_tft).fillRect(
		x + (left ? 0 : width - Lcars_B_Width), 
		y + (top ? _posRadius : 0), 
		Lcars_B_Width, 
		height - _posRadius, 
		color
	);
	// positive radius
	uint16_t posCircX = x + Lcars_Pos_Radius + (left ? 0 : width - (Lcars_Pos_Radius * 2 + 1));
	uint16_t posCircY = y + Lcars_Pos_Radius + (top ? 0 : height - (Lcars_Pos_Radius * 2 + 1));
	(*_tft).fillCircleHelper(
		posCircX,
		posCircY,
		Lcars_Pos_Radius,
		(left ? 2 : 1),
		0,
		color
	);
	// Fill gap
	(*_tft).fillRect(
		posCircX + (left ? 0 : -Lcars_Pos_Radius +1),
		posCircY + (top ? -Lcars_Pos_Radius : +1),
		Lcars_Pos_Radius,
		Lcars_Pos_Radius,
		color
	);
	// horizontal
	(*_tft).fillRect(
		x + (left ? Lcars_B_Width : 0),
		y + (top ? 0 : height - Lcars_Bar_Height),
		width - Lcars_B_Width,
		Lcars_Bar_Height,
		color
	);
	// Fill outer
	(*_tft).fillRect(
		x + (left ? Lcars_B_Width : width - Lcars_B_Width - Lcars_Neg_Radius),
		y + (top ? Lcars_Bar_Height : height - Lcars_Bar_Height - Lcars_Neg_Radius),
		Lcars_Neg_Radius,
		Lcars_Neg_Radius,
		color
	);
	// Trim outer
	(*_tft).fillCircleHelper(
		x + (left ? Lcars_B_Width + Lcars_Neg_Radius : width - Lcars_B_Width - Lcars_Neg_Radius - 1), 
		y + (top ? Lcars_Bar_Height + Lcars_Neg_Radius : height - Lcars_Bar_Height - Lcars_Neg_Radius - 1), 
		Lcars_Neg_Radius, 
		(left ? 2 : 1), 
		0,
		Lcars_Color_Black
	);
}

void Lcars::render() {
	LcarsDisplay main = LcarsDisplay(
		this,
		_tft,
		Lcars_Color_Brown,
		0, 0,
		_width32,
		_height,
		1,
		"starfleet data p 8863"
	);
	LcarsDisplay aux = LcarsDisplay(
		this,
		_tft,
		Lcars_Color_Orange,
		_width32, 0,
		_width3,
		_height,
		0,
		"aux"
	);
	main.begin();
	aux.begin();

	main.setColor(Lcars_Color_Brown);
	aux.setColor(Lcars_Color_Orange);

	log(strlen(aux.getName()));
}

void Lcars::grid(
	uint16_t x, uint16_t y,
	uint16_t width, uint16_t height,
	uint8_t xPeriod, uint8_t yPeriod,
	uint8_t xOffset, uint8_t yOffset,
	uint16_t color
) {
	uint16_t _x = x + (xOffset % xPeriod);
	uint16_t _y = y + (yOffset % yPeriod);

	uint16_t endX = x + width - 1;
	uint16_t endY = y + height - 1;

	while (_x <= endX) {
		(*_tft).drawFastVLine(_x, y, height, color);
		_x = _x + xPeriod;
	}

	while (_y <= endY) {
		(*_tft).drawFastHLine(x, _y, width, color);
		_y = _y + yPeriod;
	}
}

bool Lcars::isLeft(uint8_t corner) {
	return corner % 4 == 0 || corner % 4 == 3;
}

bool Lcars::isTop(uint8_t corner) {
	return corner % 4 < 2;
}

























