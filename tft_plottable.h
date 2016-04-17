#ifndef TFT_PLOTTABLE_H
#define TFT_PLOTTABLE_H

#include "SPFD5408_Adafruit_GFX.h"

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class Plottable
{
private:
	bool _visible;
	uint16_t _size_x;
	uint16_t _size_y;
	
	void (*_callback)();

public:
	Plottable();
	Plottable(void (*callback)());
	Plottable(void (*callback)(), uint16_t size_x, uint16_t size_y);
	
	bool getVisible();
	void setVisible(bool visible = true);
	void setInvisible();
	virtual void draw(Adafruit_GFX &tft, uint16_t x0, uint16_t y0) = 0;
	virtual void callback();

	virtual void resize(){};
	uint16_t getSizeX();
	uint16_t getSizeY();
	void setSizeX(uint16_t size_x);
	void setSizeY(uint16_t size_y);
};

#endif //PLOTTABLE_H
