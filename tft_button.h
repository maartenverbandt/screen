#ifndef TFT_BUTTON_H
#define TFT_BUTTON_H

#include "tft_button_interface.h"

class TFTButton : public TFTButtonInterface
{
private:
	char _text[20];
	uint16_t _text_color;
	uint8_t _text_size;
	
	uint16_t _button_color;

public:	
	TFTButton(void (*callback)(), char* text);
	TFTButton(void (*callback)(), char* text, uint16_t size_x, uint16_t size_y);

	void draw(Adafruit_GFX &tft, uint16_t x0, uint16_t y0);

	char* getText();
	void setText(char* text);
	uint16_t getTextColor();
	void setTextColor(uint16_t color);
	uint8_t getTextSize();
	void setTextSize(uint8_t text_size);
	
	uint16_t getButtonColor();
	void setButtonColor(uint16_t color);

};

#endif //TFT_BUTTON_H
