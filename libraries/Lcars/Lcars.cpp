#include "Lcars.h"
#include <Adafruit_GFX.h>;
#include "Adafruit_ILI9340.h";
#include <Interruptions.h>;
#include "LcarsDisplay.h";
#include "LcarsLed.h";

Lcars::Lcars(Adafruit_ILI9340* tft)
{
	_tft = tft;
	_posRadius = Lcars_B_Width / 2;
	_negRadius = Lcars_B_Width / 4;
	_interruptions = Interruptions();
}

void Lcars::begin() {
  	_width = (*_tft).width();
  	_height = (*_tft).height() / 3 * 2;
  	_width3 = _width / 3;
  	_width32 = _width3 * 2;
  	_geo.setTft(_tft);
	_geo.setColor(Lcars_Color_GREEN);
	_geo.setX(0);
	_geo.setY(_height);
	_geo.setPin(0);
	_geo.setWidth(30);
	_geo.setHeight(30);
	_bio.setTft(_tft);
	_bio.setColor(Lcars_Color_GREEN);
	_bio.setX(60);
	_bio.setY(_height);
	_bio.setPin(0);
	_bio.setWidth(30);
	_bio.setHeight(30);
	_met.setTft(_tft);
	_met.setColor(Lcars_Color_GREEN);
	_met.setX(30);
	_met.setY(_height);
	_met.setPin(0);
	_met.setWidth(30);
	_met.setHeight(30);

	uint16_t chaserX = _width - 20;
	uint16_t chaserY = (*_tft).height() - 60;

	_ch1.setTft(_tft);
	_ch1.setColor(Lcars_Color_RED);
	_ch1.setX(chaserX);
	_ch1.setY(chaserY);
	_ch1.setPin(0);
	_ch1.setWidth(20);
	_ch1.setHeight(15);

	_ch2.setTft(_tft);
	_ch2.setColor(Lcars_Color_GREEN);
	_ch2.setX(chaserX);
	_ch2.setY(chaserY + 15);
	_ch2.setPin(0);
	_ch2.setWidth(20);
	_ch2.setHeight(15);

	_ch3.setTft(_tft);
	_ch3.setColor(Lcars_Color_GREEN);
	_ch3.setX(chaserX);
	_ch3.setY(chaserY + 30);
	_ch3.setPin(0);
	_ch3.setWidth(20);
	_ch3.setHeight(15);

	_ch4.setTft(_tft);
	_ch4.setColor(Lcars_Color_GREEN);
	_ch4.setX(chaserX);
	_ch4.setY(chaserY + 45);
	_ch4.setPin(0);
	_ch4.setWidth(20);
	_ch4.setHeight(15);

  	setMode(Lcars_Mode_Medical);
}

void Lcars::setMode(uint8_t mode) {
	_mode = mode;
	render();
	// play(Lcars_Sound_Scan);
}

void Lcars::log(const char* message) {
	(*_tft).println(message);
}

void Lcars::log(unsigned int n) {
	(*_tft).println(n, 10);
}

// void Lcars::play(uint8_t file) {
// 	char name[30];
// 	char ext[] = ".wav";
// 	itoa(file, name, 10);
// 	strcat(name, ext);
// 	(*_tmrpcm).play(name);
// }

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
		"medical"
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
}

void Lcars::tick(unsigned long millis) {
	// (*_tft).setCursor(30, _height);
	// (*_tft).setTextColor(Lcars_Color_White, Lcars_Color_Black);
	// (*_tft).println(millis);
	uint16_t halfsecs = millis / 200;
	uint8_t quadsecs = halfsecs % 4;
	if (halfsecs % 4 == 0) {
		_geo.on();
		_ch4.on();
	} else {
		_geo.off();
		_ch4.off();
	}
	if (halfsecs % 4 == 1) {
		_met.on();
		_ch3.on();
	} else {
		_met.off();
		_ch3.off();
	}
	if (halfsecs % 4 == 2) {
		_bio.on();
		_ch2.on();
	} else {
		_bio.off();
		_ch2.off();
	}

	if (halfsecs % 4 == 3) {
		_ch1.on();
	} else {
		_ch1.off();
	}
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

























