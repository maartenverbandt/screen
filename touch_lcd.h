#ifndef TOUCH_LCD_H
#define TOUCH_LCD_H

// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_TFTLCD.h>
#include <SPFD5408_TouchScreen.h>
// -- End

typedef struct calibration_pair_t{
	uint16_t tft;
	uint16_t touch;
} calibration_pair_t;

class TouchLCD : public Adafruit_TFTLCD, public TouchScreen
{
private:	
	//calibration utilities
	uint16_t _calibration_pair_counter;
	uint16_t _calibration_pair_goal;
	calibration_pair_t _x[2];
	calibration_pair_t _y[2];
	
	int16_t _offset_x, _offset_y;
	float _scale_x, _scale_y;
	
	void drawNextCalibrationPoint();
	void addCalibrationPoint(TSPoint p);
	
protected:
	const uint8_t _cs,_cd,_wr,_rd,_rs,_xp,_yp,_xm,_ym;

public:
	TouchLCD(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t rs, uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);
	
	void startCalibration();
	void drawCalibrationPoint(uint16_t x, uint16_t y);
	void finishCalibration();

	bool update();
	virtual void controlTFT(){}; 
	
	int16_t offsetX();
	int16_t offsetY();
	float scaleX();
	float scaleY();
	
	void setOffsetX(int16_t offset_x);
	void setOffsetY(int16_t offset_y);
	void setScaleX(float scale_x);
	void setScaleY(float scale_y);
	
	TSPoint getTFTPoint();
};

#endif //TOUCH_LCD_H
