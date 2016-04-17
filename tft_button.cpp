#include "tft_button.h"

TFTButton::TFTButton(void (*callback)(), char* text) : 
	Plottable(callback),
	_button_color(BLUE),
	_text_color(WHITE)
{
	setText(text);
}

TFTButton::TFTButton(void (*callback)(), char* text, uint16_t size_x, uint16_t size_y) : 
	Plottable(callback, size_x, size_y),
	_button_color(BLUE),
	_text_color(WHITE)
{
	setText(text);
}

void TFTButton::draw(Adafruit_GFX &tft, uint16_t x0, uint16_t y0)
{
	//draw the rectangle
	tft.fillRoundRect(x0, y0, getSizeX(), getSizeY(), 4, _button_color);
	
	//set the centered text
	//compute the text size
	uint8_t text_length = 0;
	while((text_length<20) && (_text[text_length] != '\0')){
		text_length++;
	}
	if(text_length>=20){
		text_length = 20;
	}
	
	//print button centered text
	uint16_t cursor_x = x0 + (getSizeX() - text_length*6)/2;
	uint16_t cursor_y = y0 + (getSizeY() - 4)/2;
	tft.setCursor(cursor_x, cursor_y);
	tft.setTextColor(_text_color);
	tft.setTextSize(_text_size);
	tft.setTextWrap(false);
	tft.print(_text);	
}

bool TFTButton::getCheckable()
{
	return _checkable;
}

void TFTButton::setCheckable(bool checkable)
{
	_checkable = checkable;
}

bool TFTButton::getChecked()
{
	return _checked;
}

void TFTButton::setChecked(bool checked)
{
	_checked = checked;
}

char* TFTButton::getText()
{
	return _text;
}

void TFTButton::setText(char* text){	
	memcpy(_text, text, 20);
}

uint8_t TFTButton::getTextSize(){
	return _text_size;
}

void TFTButton::setTextSize(uint8_t text_size)
{
	_text_size = text_size;
}

uint16_t TFTButton::getButtonColor()
{
	return _button_color;
}

void TFTButton::setButtonColor(uint16_t color)
{
	_button_color = color;
}

uint16_t TFTButton::getTextColor()
{
	return _text_color; 
}

void TFTButton::setTextColor(uint16_t color)
{
	_text_color = color;
}
