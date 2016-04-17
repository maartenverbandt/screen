#include "tft_page.h"

TFTPage::TFTPage(uint16_t page_color) : 
	Plottable(),
	_number_of_plottables(0),
	_plottables(NULL),
	_page_color(page_color)
{	
	//do nothing
}

TFTPage::TFTPage(uint16_t page_size_x, uint16_t page_size_y, uint16_t page_color) : 
	Plottable(NULL, page_size_x, page_size_y),
	_number_of_plottables(0),
	_plottables(NULL),
	_page_color(page_color)
{	
	//do nothing
}

void TFTPage::draw(Adafruit_GFX &tft, uint16_t x, uint16_t y)
{
	tft.fillScreen(_page_color);
	
	uint16_t k;
	for(k=0;k<_number_of_plottables;k++){
		_plottables[k].plottable->draw(tft, _plottables[k].x, _plottables[k].y);
	}
}

Plottable* TFTPage::touch(uint16_t x, uint16_t y)
{
	uint16_t k;
	for(k=0;k<_number_of_plottables;k++){
		if((x > _plottables[k].x) &&
		   (x < _plottables[k].x + _plottables[k].plottable->getSizeX()) &&
		   (y > _plottables[k].y) &&
		   (y < _plottables[k].y + _plottables[k].plottable->getSizeY()))
		{   
			_plottables[k].plottable->callback();
			return _plottables[k].plottable;
		}
	}
	
	return NULL;
}

void TFTPage::addPlottable(Plottable* plottable, uint16_t x, uint16_t y)
{
	// extend array
	plottable_t* copy = new plottable_t[_number_of_plottables+1];
	memcpy(copy,_plottables,_number_of_plottables*sizeof(plottable_t));
	
	// add new plottable to the new array
	copy[_number_of_plottables].plottable = plottable;
	copy[_number_of_plottables].x = x;
	copy[_number_of_plottables].y = y;
	
	// delete the previous array and make _plottables point to the new array
	delete _plottables;
	_plottables = copy;
	_number_of_plottables++;
}
