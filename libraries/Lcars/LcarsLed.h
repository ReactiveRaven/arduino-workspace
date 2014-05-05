#ifndef _Lcars_Led_
#define _Lcars_Led_

class LcarsLed {
	public:
		LcarsDisplay(
			Adafruit_ILI9340* tft, 
			uint16_t color,
			uint16_t x,
			uint16_t y, 
			uint16_t width,
			uint16_t height
		);

		void 
			begin(void),
			clear(void),
			CLEAR(void),
			setCorner(uint8_t corner);

	private:
		void render(void);
		Adafruit_ILI9340* _tft;
		int16_t _x, _y, _ix, _iy, _width, _height, _iwidth, _iheight, _color;
		bool top, left;
};

#endif