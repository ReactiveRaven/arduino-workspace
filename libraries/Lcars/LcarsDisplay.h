#ifndef _Lcars_Display_
#define _Lcars_Display_

class LcarsDisplay {
	public:
		LcarsDisplay(
			Lcars* lcars, 
			Adafruit_ILI9340* tft, 
			uint16_t color,
			uint16_t x,
			uint16_t y, 
			uint16_t width,
			uint16_t height,
			uint8_t corner,
			char* name
		);

		void 
			begin(void),
			setMode(uint8_t mode),
			clear(void),
			CLEAR(void),
			setCorner(uint8_t corner),
			setColor(uint16_t color),
			setName(char* name);

		const char*
			getName(void);

	private:
		void
			render(void),
			renderShoulder(void);
		Lcars* _lcars;
		Adafruit_ILI9340* _tft;
		uint8_t _mode, _corner, _namewidth;
		int16_t _x, _y, _ix, _iy, _width, _height, _iwidth, _iheight, _color;
		bool top, left;
		char _name[30];
};

#endif