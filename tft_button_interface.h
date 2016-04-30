#ifndef TFT_BUTTON_INTERFACE_H
#define TFT_BUTTON_INTERFACE_H

#include <tft_plottable.h>

class TFTButtonInterface : public Plottable
{
private:
	bool _checkable;
	bool _checked;

public:
	TFTButtonInterface(void (*callback)());
	TFTButtonInterface(void (*callback)(), uint16_t size_x, uint16_t size_y);

	virtual void draw(Adafruit_GFX &tft, uint16_t x0, uint16_t y0) = 0;

	bool getCheckable();
	void setCheckable(bool checkable = true);
	bool getChecked();
	void setChecked(bool checked = true);

};

#endif //TFT_BUTTON_INTERFACE_H
