#ifndef TFT_GRID_H
#define TFT_GRID_H

#include "tft_page.h"

class TFTGrid : public TFTPage
{
private:
	uint16_t _rows;
	uint16_t _columns;

public:
	TFTGrid(uint16_t rows, uint16_t columns, uint16_t page_size_x, uint16_t page_size_y, uint16_t page_color = BLACK);

	void addPlottableToGrid(Plottable *plottable, uint16_t row, uint16_t column);
};

#endif //TFT_GRID_H
