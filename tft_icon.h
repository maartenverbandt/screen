#ifndef TFT_ICON_H
#define TFT_ICON_H

#include <tft_button_interface.h>
#include <SPI.h>
#include <SD.h>

typedef struct bmp_header_t {
	uint16_t signature;
	uint32_t filesize;
	uint32_t creator;
	uint32_t imageoffset;
	uint32_t headersize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t depth;
	uint32_t compression;
} bmp_header_t;

class TFTIcon : public TFTButtonInterface
{
private:
	char _filename[13];
	
	bool _header_parsed;
	bmp_header_t _image_data;
	
	/*uint16_t read16(File f);
	uint32_t read32(File f);*/

public:
	TFTIcon(void (*callback)(), char* filename);

	bool parseHeader(bool force = false);
	void draw(Adafruit_GFX &tft, uint16_t x0, uint16_t y0);
	
};

#endif //TFT_ICON_H
