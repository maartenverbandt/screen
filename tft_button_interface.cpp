#include "tft_button_interface.h"

TFTButtonInterface::TFTButtonInterface(void (*callback)()) : 
	Plottable(callback)
{
	//do nothing
}

TFTButtonInterface::TFTButtonInterface(void (*callback)(), uint16_t size_x, uint16_t size_y) : 
	Plottable(callback, size_x, size_y)
{
	//do nothing
}

bool TFTButtonInterface::getCheckable()
{
	return _checkable;
}

void TFTButtonInterface::setCheckable(bool checkable)
{
	_checkable = checkable;
}

bool TFTButtonInterface::getChecked()
{
	return _checked;
}

void TFTButtonInterface::setChecked(bool checked)
{
	_checked = checked;
}
