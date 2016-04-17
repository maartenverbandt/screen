#ifndef TFT_PAGE_H
#define TFT_PAGE_H

#include "tft_plottable.h"

typedef struct plottable_t{
	Plottable *plottable;
	uint16_t x;
	uint16_t y;
} plottable_t;

class TFTPage : public Plottable
{
private:
	uint16_t _number_of_plottables;
	plottable_t* _plottables;
	
	uint16_t _page_color;

public:
	TFTPage(uint16_t page_color = BLACK);
	TFTPage(uint16_t page_size_x, uint16_t page_size_y, uint16_t page_color = BLACK);
	
	void draw(Adafruit_GFX &tft, uint16_t x = 0, uint16_t y = 0);
	Plottable* touch(uint16_t x, uint16_t y);

	void addPlottable(Plottable* plottable, uint16_t x, uint16_t y);
};

#endif //TFT_PAGE_H
