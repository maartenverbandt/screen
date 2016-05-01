#include <tft_icon.h>

TFTIcon::TFTIcon() :
	TFTButtonInterface(NULL)
{
	//do nothing
}

TFTIcon::TFTIcon(void (*callback)(), char* filename) :
	TFTButtonInterface(callback)
{
	memcpy(_filename, filename, 13);
	//READ SIZE OF THE PICTURE
}

#define BUFFPIXEL 20

void TFTIcon::draw(Adafruit_GFX &tft, uint16_t x0, uint16_t y0)
{
  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x0 >= tft.width()) || (y0 >= tft.height())) return;

  // Open requested file on SD card
  if ((bmpFile = SD.open(_filename)) == NULL) {
  	Serial.println("File not found.");
  
    //MAKE DUMMY IMAGE
  	setSizeX(100);
  	setSizeY(70);
    
    //draw the rectangle
	tft.fillRoundRect(x0, y0, getSizeX(), getSizeY(), 4, 0xFFFF);
	
	//set the centered text
	//compute the text size
	uint8_t text_length = 0;
	while((text_length<20) && (_filename[text_length] != '\0')){
		text_length++;
	}
	if(text_length>=20){
		text_length = 20;
	}
	
	//print button centered text
	uint16_t cursor_x = x0 + (getSizeX() - text_length*6)/2;
	uint16_t cursor_y = y0 + (getSizeY() - 4)/2;
	tft.setCursor(cursor_x, cursor_y);
	tft.setTextColor(0x0000);
	tft.setTextSize(1);
	tft.setTextWrap(false);
	tft.print("/");	tft.print(_filename);	
    
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
  	(void)read32(bmpFile); // Read & ignore file size data
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    (void)read32(bmpFile); // Read & ignore header size data
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    
  	setSizeX(bmpWidth);
  	setSizeY(bmpHeight);
  	
  	Serial.println("File found:");
  	Serial.println(bmpWidth);
  	Serial.println(bmpHeight);
    
    //Plot the image
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
        goodBmp = true; // Supported BMP format -- proceed!
        
        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x0+w-1) >= tft.width())  w = tft.width()  - x0;
        if((y0+h-1) >= tft.height()) h = tft.height() - y0;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x0, y0, x0+w-1, y0+h-1);

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if(lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        }
      } // end goodBmp
    }
    
  }

  bmpFile.close();
}

uint16_t TFTIcon::read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t TFTIcon::read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
