#ifndef TFT_CALIBRATOR_H
#define TFT_CALIBRATOR_H

#include "SPFD5408_TouchScreen.h"
#include "SPFD5408_Adafruit_GFX.h"

typedef struct calibration_pair_t{
	uint16_t tft;
	uint16_t touch;
} calibration_pair_t;

class TFTCalibrator
{
private:
	uint16_t _calibration_pair_counter;
	uint16_t _calibration_pair_goal;
	calibration_pair_t _x[4];
	calibration_pair_t _y[4];
	
	Adafruit_GFX &_tft;
	TouchScreen &_touch;
	
	int16_t _offset_x, _offset_y;
	float _scale_x, _scale_y;
	
	void drawNextCalibrationPoint();
	void addCalibrationPoint(TSPoint p);

public:
	TFTCalibrator(Adafruit_GFX &tft, TouchScreen &touch);

	void startCalibration(uint16_t number_of_points = 2);
	void drawCalibrationPoint(uint16_t x, uint16_t y);
	void finishCalibration();

	bool update();
	//bool updateSimple();
	
	int16_t offsetX();
	int16_t offsetY();
	float scaleX();
	float scaleY();

};

#endif //TFT_CALIBRATOR_H
