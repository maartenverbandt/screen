#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touch library

#include <tft_button.h>
#include <tft_page.h>
#include <tft_calibrator.h>

// Calibrates value
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//These are the pins for the shield!
#define YP A3 
#define XM A2 
#define YM 9  
#define XP 8


// LCD Pin

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4 // Optional : otherwise connect to Arduino's reset pin

// Init LCD

static Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Init TouchScreen:

TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY, &tft);

// Init Calibrator

static TFTCalibrator calibrator(tft,ts);
static TSPoint pg;

void setup(void) {
	Serial.begin(9600);

	//tft setup
	tft.reset();
	tft.begin(0x9341);
	tft.setRotation(0); // Need for the Mega, please changed for your choice or rotation initial 
	
	calibrator.startCalibration();
}	
	
void loop()
{	
	while(!calibrator.update())
		delay(10);
		
	tft.fillScreen(GREEN);
	while(1)
		delay(1000);
}

TSPoint waitOneTouch() {
  TSPoint p;
  
  do {
    p= ts.getPoint(); 
  
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);
  
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
  
  p.x = p.x*0.3125;
  p.y = p.y*0.2344;
  
  Serial.print(p.x); Serial.print(", "); Serial.println(p.y);
  
  return p;
}
