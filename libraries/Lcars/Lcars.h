#ifndef _Lcars_
#define _Lcars_

#include <Adafruit_GFX.h>;
#include "Adafruit_ILI9340.h";
#include <Interruptions.h>;

#define Lcars_Color_Lavender      0x9CD9
#define Lcars_Color_Purple        0x9CDF
#define Lcars_Color_Lilac         0xCCD9
#define Lcars_Color_Pink          0xCB33
#define Lcars_Color_Brown         0xCB2C
#define Lcars_Color_Peach         0xFCCC
#define Lcars_Color_Orange        0xFCC0
#define Lcars_Color_Yellow        0xFE6C
#define Lcars_Color_Black         0x0000
#define Lcars_Color_White         0xFFFF
#define Lcars_Color_Lavender_Dark 0x31AC
#define Lcars_Color_Purple_Dark   0x0851
#define Lcars_Color_Lilac_Dark    0x61AC
#define Lcars_Color_Pink_Dark     0x7149
#define Lcars_Color_Brown_Dark    0x7144
#define Lcars_Color_Peach_Dark    0x91C0
#define Lcars_Color_Orange_Dark   0x9AC0
#define Lcars_Color_Yellow_Dark   0x9340
#define Lcars_Color_GREEN         0x07E0
#define Lcars_Color_RED           0xF986
#define Lcars_Color_BLUE          0x001F

#define Lcars_B_Width    30
#define Lcars_B_Height   (Lcars_B_Width / 2.5)
#define Lcars_Bar_Height 7
//(Lcars_B_Width / 5)
#define Lcars_Pos_Radius (Lcars_B_Width / 2)
#define Lcars_Neg_Radius (Lcars_B_Width / 4)
#define Lcars_B_VSpacing (Lcars_B_Width / 30)
#define Lcars_B_HSpacing (Lcars_B_Width / 30)
#define Lcars_B_Padding (Lcars_B_Width / 2)
#define Lcars_B_Padding2 (Lcars_B_Padding * 2)

#define Lcars_Mode_Debug   1
#define Lcars_Mode_Medical 2

class Lcars {
	public:
		Lcars(Adafruit_ILI9340* tft);

		void 
			begin(void),
			setMode(uint8_t mode),
			log(const char* msg),
		    log(unsigned int n),
			shoulder(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t corner, uint16_t color),
		    grid(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t xPeriod, uint8_t yPeriod, uint8_t xOffset, uint8_t yOffset, uint16_t color);

	    bool
	    	isLeft(uint8_t corner),
		    isTop(uint8_t corner);

	private:
		void
			render(void);
		Adafruit_ILI9340* _tft;
		Interruptions _interruptions;
		uint8_t _mode, _posRadius, _negRadius;
		int16_t _width, _height, _width3, _width32;
};

#include "LcarsDisplay.h";

#endif