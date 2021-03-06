#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touch library

#include <tft_button.h>
#include <tft_page.h>

// Calibrates value
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//These are the pins for the shield!
#define YP A3 
#define XM A2 
#define YM 9  
#define XP 8

// Init TouchScreen:

TouchScreen ts = TouchScreen(XP, YP, XM, YM);

// LCD Pin

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4 // Optional : otherwise connect to Arduino's reset pin

// Init LCD

static Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

static TFTPage page_front = TFTPage();
static TFTPage page_back = TFTPage();
static TFTPage* current_page;
static TSPoint pg;

static void button_front_callback()
{
	current_page = &page_back;
	current_page->draw(tft);
	delay(200);
}

static void button_back_callback()
{
	current_page = &page_front;
	current_page->draw(tft);
	delay(200);
}

static TFTButton button_front = TFTButton(button_front_callback, "Front", 100, 70);
static TFTButton button_back = TFTButton(button_back_callback, "Back", 100, 70);
static TFTButton button_extra = TFTButton(NULL, "Extra", 100, 70);

void setup(void) {
	Serial.begin(9600);

	//tft setup
	tft.reset();
	tft.begin(0x9341);
	tft.setRotation(1); // Need for the Mega, please changed for your choice or rotation initial 
	
	page_front.addPlottable(&button_front, 110, 85);
	page_front.addPlottable(&button_extra, 220, 85);
	page_back.addPlottable(&button_back, 110, 85);
	
	current_page = &page_front;
	current_page->draw(tft);
	
	//tft.fillRect(0, 0, 100, 100, BLUE);
	//button_front.draw(tft,100,100);
	
}	
	
void loop()
{	
	pg = waitOneTouch();
	current_page->touch(pg.x,pg.y);
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
