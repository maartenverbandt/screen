#ifndef SPFD5408_H
#define SPFD5408_H

#include <touch_lcd.h>

#define SPFD5408_CS A3
#define SPFD5408_CD A2
#define SPFD5408_WR A1
#define SPFD5408_RD A0
#define SPFD5408_RESET A4

#define SPFD5408_YP A3 
#define SPFD5408_XM A2 
#define SPFD5408_YM 9  
#define SPFD5408_XP 8
#define SPFD5408_SENSIBILITY 300

class SPFD5408 : public TouchLCD
{
public:
	SPFD5408();

	void controlTFT();

};

#endif //SPFD5408_H
