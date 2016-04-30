#ifndef TFT_ICON_H
#define TFT_ICON_H

#include <tft_button_interface.h>
#include <SPI.h>
#include <SD.h>

class TFTIcon : public TFTButtonInterface
{
private:
	char filename[13];
	
	uint16_t read16(File f);
	uint32_t read32(File f);
	void progmemPrint(const char *str);
	void progmemPrintln(const char *str);

public:
	TFTIcon();
	TFTIcon(void (*callback)(), char* filename);

	void draw(Adafruit_GFX &tft, uint16_t x0, uint16_t y0);
	
};

#endif //TFT_ICON_H
