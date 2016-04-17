#include "tft_plottable.h"

Plottable::Plottable() : 
	_visible(false),
	_size_x(0),
	_size_y(0),
	_callback(NULL)
{
	//do nothing
}

Plottable::Plottable(void (*callback)()) : 
	_visible(false),
	_size_x(0),
	_size_y(0),
	_callback(callback)
{
	//do nothing
}

Plottable::Plottable(void (*callback)(), uint16_t size_x, uint16_t size_y) : 
	_visible(false),
	_size_x(size_x),
	_size_y(size_y),
	_callback(callback)
{
	//do nothing
}

void Plottable::callback()
{
	if(_callback != NULL){
		_callback();
	}
}

bool Plottable::getVisible()
{
	return _visible;
}

void Plottable::setVisible(bool visible)
{
	_visible = visible;
}

void Plottable::setInvisible()
{
	_visible = false;
}

uint16_t Plottable::getSizeX()
{
	return _size_x;
}

uint16_t Plottable::getSizeY()
{
	return _size_y;
}

void Plottable::setSizeX(uint16_t size_x)
{
	_size_x = size_x;
}

void Plottable::setSizeY(uint16_t size_y)
{
	_size_y = size_y;
}
