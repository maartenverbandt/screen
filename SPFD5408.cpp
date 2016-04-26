#include "SPFD5408.h"

SPFD5408::SPFD5408() : 
	Adafruit_TFTLCD(SPFD5408_CS, SPFD5408_CD, SPFD5408_WR, SPFD5408_RD, SPFD5408_RESET), TouchScreen(SPFD5408_XP, SPFD5408_YP, SPFD5408_XM, SPFD5408_YM), 
	_cs(SPFD5408_CS), _cd(SPFD5408_CD), _wr(SPFD5408_WR), _rd(SPFD5408_RD)
{
	
}

void SPFD5408::controlTFT()
{
	pinMode(_cs, OUTPUT);    // Enable outputs
	pinMode(_cd, OUTPUT);
	pinMode(_wr, OUTPUT);
	pinMode(_rd, OUTPUT);
}
