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

typedef struct calibration_pair_t{
	uint16_t tft;
	uint16_t touch;
} calibration_pair_t;

class SPFD5408 : public Adafruit_TFTLCD, public TouchScreen
{
private:
	const uint8_t _cs,_cd,_wr,_rd;
	
	//calibration utilities
	uint16_t _calibration_pair_counter;
	uint16_t _calibration_pair_goal;
	calibration_pair_t _x[2];
	calibration_pair_t _y[2];
	
	int16_t _offset_x, _offset_y;
	float _scale_x, _scale_y;
	
	void drawNextCalibrationPoint();
	void addCalibrationPoint(TSPoint p);

public:
	SPFD5408();
	
	void controlTFT();

	void startCalibration();
	void drawCalibrationPoint(uint16_t x, uint16_t y);
	void finishCalibration();

	bool update();
	
	int16_t offsetX();
	int16_t offsetY();
	float scaleX();
	float scaleY();
};
#endif //_SPFD5408_H_
