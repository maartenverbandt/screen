#include <SPFD5408.h>    // Core graphics library
#include <tft_button.h>
#include <tft_page.h>

// Calibrates value
#define MINPRESSURE 10
#define MAXPRESSURE 1000

static SPFD5408 tft;

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
}	
	
void loop()
{	
	pg = waitOneTouch();
	current_page->touch(pg.x,pg.y);
}

TSPoint waitOneTouch() {
  TSPoint p;
  
  do {
    p= tft.getPoint(); 
  
    //pinMode(XM, OUTPUT); //Pins configures again for TFT control
    //pinMode(YP, OUTPUT);
    tft.controlTFT();
  
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
  
  p.x = p.x*0.3125;
  p.y = p.y*0.2344;
  
  Serial.print(p.x); Serial.print(", "); Serial.println(p.y);
  
  return p;
}
