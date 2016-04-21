#ifndef TFT_CALIBRATOR_H
#define TFT_CALIBRATOR_H

typedef struct calibration_pair_t{
	uint16_t tft;
	uint16_t touch;
} calibration_pair_t;

class TFTCalibrator
{
private:
	uint16_t _calibration_pair_counter;
	uint16_t _calibration_pair_goal;
	calibration_pair_t _x[2];
	calibration_pair_t _y[2];
	
	const uint16_t _fixed_calibration_points[2];
	
	Adafruit_GFX &_tft;
	TouchScreen &_touch;
	
	void addCalibrationPoint();

public:
	TFTCalibrator(Adafruit_GFX &tft, TouchScreen &touch);

	void startCalibration(uint16_t number_of_points = 2);
	void drawCalibrationPoint(uint16_t x, uint16_t y);
	void finishCalibration();

	bool update();
	


};

#endif //TFT_CALIBRATOR_H
