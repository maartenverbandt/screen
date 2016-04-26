#ifndef _SPFD5408_H_
#define _SPFD5408_H_

// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_TFTLCD.h>
#include <SPFD5408_TouchScreen.h>
// -- End


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

class SPFD5408 : public Adafruit_TFTLCD, public TouchScreen
{
private:
	const uint8_t _cs,_cd,_wr,_rd;

public:
	SPFD5408();
	
	void controlTFT();

};
#endif //_SPFD5408_H_
