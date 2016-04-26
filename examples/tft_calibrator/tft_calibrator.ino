#include <SPFD5408.h>     // Touch library

#include <tft_button.h>
#include <tft_page.h>

// Calibrates value
#define MINPRESSURE 10
#define MAXPRESSURE 1000

static SPFD5408 tft;
static TSPoint pg;

void setup(void) {
	Serial.begin(115200);

	//tft setup
	tft.reset();
	tft.begin(0x9341);
	tft.setRotation(0); // Need for the Mega, please changed for your choice or rotation initial 
	
	tft.fillScreen(GREEN);
	delay(1000);
	
	tft.startCalibration();
}	
	
void loop()
{	
	while(!tft.update()){
		//Serial.println("update");
		delay(10);
	}
	
	Serial.println("finished");
	tft.fillScreen(GREEN);
	tft.setTextColor(0x0000);
	tft.setTextSize(2);
	
	tft.print("Offset X: "); tft.println(tft.offsetX());
	tft.print("Offset Y: "); tft.println(tft.offsetY());
	tft.print("Scale X: "); tft.println(tft.scaleX());
	tft.print("Scale Y: "); tft.println(tft.scaleY()); 
}

TSPoint waitOneTouch() {
  TSPoint p;
  
  do {
    p= tft.getPoint(); 
  
    tft.controlTFT();
  
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
  
  p.x = p.x*0.3125;
  p.y = p.y*0.2344;
  
  Serial.print(p.x); Serial.print(", "); Serial.println(p.y);
  
  return p;
}
