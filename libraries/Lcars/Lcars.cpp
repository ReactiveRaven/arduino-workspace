#include "Lcars.h"
#include <Adafruit_GFX.h>;
#include "Adafruit_ILI9340.h";
#include <Interruptions.h>;

#define Lcars_Color_Lavender 0x9CD9
#define Lcars_Color_Purple   0x9CDF
#define Lcars_Color_Lilac    0xCCD9
#define Lcars_Color_Pink     0xCB33
#define Lcars_Color_Brown    0xCB2C
#define Lcars_Color_Peach    0xFCCC
#define Lcars_Color_Orange   0xFCC0
#define Lcars_Color_Yellow   0xFE6C
#define Lcars_Color_Black    0x0000
#define Lcars_Color_White    0xFFFF

#define Lcars_B_Width    30
#define Lcars_B_Height   12 
#define Lcars_B_VSpacing 1
#define Lcars_B_HSpacing 1

#define Lcars_Mode_Debug   1
#define Lcars_Mode_Medical 2

Lcars::Lcars(Adafruit_ILI9340* tft)
{
	_tft = tft;
	_interruptions = Interruptions();
	begin();
}

void Lcars::begin() {
	(*_tft).setRotation(1);
  	(*_tft).fillScreen(Lcars_Color_Black);
  	_width = (*_tft).width();
  	_height = (*_tft).height();
  	setMode(1);
}

void Lcars::setMode(uint8_t mode) {
	_mode = mode;
	render();
}

void Lcars::log(char message) {
	(*_tft).println(message);
}

void Lcars::shoulder(
	uint16_t x, uint16_t y,
	uint16_t width, uint16_t height,
	uint8_t corner, uint16_t color
) {
	// bool top = ((corner % 4) < 2);
	// bool left = ((corner % 4) == 0 || (corner % 4) == 3);
	(*_tft).fillRect(x, y, width, height, color);
}

void Lcars::render() {
	uint8_t qw = _width/4;
	uint8_t hh = _height/2;
  shoulder(0, 0, qw, hh, 0, Lcars_Color_Lavender);
  shoulder(qw, 0, qw, hh, 0, Lcars_Color_Purple);
  shoulder(2*qw, 0, qw, hh, 0, Lcars_Color_Lilac);
  shoulder(3*qw, 0, qw, hh, 0, Lcars_Color_Pink);

  shoulder(0, hh, qw, hh, 0, Lcars_Color_Brown);
  shoulder(qw, hh, qw, hh, 0, Lcars_Color_Peach);
  shoulder(2*qw, hh, qw, hh, 0, Lcars_Color_Orange);
  shoulder(3*qw, hh, qw, hh, 0, Lcars_Color_Yellow);
  // (*_tft).fillRect(30, 0, _width-60, 5, Lcars_Color_Orange);
  // (*_tft).fillRect(30, _height-5, _width-60, 5, Lcars_Color_Orange);
  // (*_tft).fillRect(0, 30, 30, _height-60, Lcars_Color_Orange);
  // (*_tft).fillRect(_width-30, 30, 30, _height-60, Lcars_Color_Orange);
  
  // (*_tft).fillRoundRect(0, 0, 70, 60, 30, Lcars_Color_Orange);
  // (*_tft).fillRoundRect(30, 5, 60, 90, 30, Lcars_Color_Black);
  
  // (*_tft).fillRoundRect(_width-70, 0, 70, 60, 30, Lcars_Color_Orange);
  // (*_tft).fillRoundRect(_width-90, 5, 60, 90, 30, Lcars_Color_Black);
  
  // (*_tft).fillRoundRect(0, _height-60, 70, 60, 30, Lcars_Color_Orange);
  // (*_tft).fillRoundRect(30, _height-95, 60, 90, 30, Lcars_Color_Black);
  
  // (*_tft).fillRoundRect(_width-70, _height-60, 70, 60, 30, Lcars_Color_Orange);
  // (*_tft).fillRoundRect(_width-90, _height-95, 60, 90, 30, Lcars_Color_Black);
  
  
  // (*_tft).fillRect(70, 0, 20, 5, Lcars_Color_Black);
  // (*_tft).fillRect(70, _height-5, 20, 5, Lcars_Color_Black);

  // (*_tft).fillRect(0, 90, 30, 30, Lcars_Color_Black);
  // (*_tft).fillRect(_width-30, _height-90, 30, 30, Lcars_Color_Black);
}