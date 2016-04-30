#include <SPFD5408.h>

SPFD5408::SPFD5408() : 
	TouchLCD(SPFD5408_CS, SPFD5408_CD, SPFD5408_WR, SPFD5408_RD, SPFD5408_RESET, SPFD5408_XP, SPFD5408_YP, SPFD5408_XM, SPFD5408_YM)
{
	setOffsetX(-900);
	setOffsetY(-900);
	setScaleX(-0.32f);
	setScaleY(-0.43f);
}

void SPFD5408::controlTFT()
{
	pinMode(_cs, OUTPUT);    // Enable outputs
	pinMode(_cd, OUTPUT);
	pinMode(_wr, OUTPUT);
	pinMode(_rd, OUTPUT);
}
