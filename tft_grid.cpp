#include "tft_grid.h"

TFTGrid::TFTGrid(uint16_t rows, uint16_t columns, uint16_t page_size_x, uint16_t page_size_y, uint16_t page_color) :
	TFTPage(page_size_x, page_size_y, page_color),
	_rows(rows),
	_columns(columns)
{
	//do nothing
}

void TFTGrid::addPlottableToGrid(Plottable *plottable, uint16_t row, uint16_t column)
{
	uint16_t dx = getSizeX()/_columns;
	uint16_t dy = getSizeY()/_rows;
	
	uint16_t x = (dx-plottable->getSizeX())/2;
	x += dx*column;
	uint16_t y = (dy-plottable->getSizeY())/2;
	y + dy*row;
	
	addPlottable(plottable, x, y);
}
