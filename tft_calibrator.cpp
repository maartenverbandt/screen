#include "tft_calibrator.h"

#define NORM2(x) x*x 

TFTCalibrator::TFTCalibrator(Adafruit_GFX &tft, TouchScreen &touch) :
	_tft(tft),
	_touch(touch),
	_calibration_pair_counter(0),
	_calibration_pair_goal(0)
{
	
}

void TFTCalibrator::startCalibration(uint16_t number_of_points)
{
	_calibration_pair_counter = 0;
	_calibration_pair_goal = number_of_points;
	
	_tft.setRotation(0);
}

void TFTCalibrator::drawCalibrationPoint(uint16_t x, uint16_t y)
{
	_x[_calibration_pair_counter].tft = x;
	_y[_calibration_pair_counter].tft = y;
	
	_tft.fillScreen(0x00);
	_tft.fillCircle(x,y,4,0xFF);
}

void TFTCalibrator::finishCalibration()
{
	int16_t _offset_x, _offset_y;
	float _scale_x, _scale_y;

	_offset_x = (_x[0].tft*_x[2].touch - _x[1].tft*_x[0].touch)/(_x[1].tft - _x[0].tft);
	_offset_y = (_y[0].tft*_y[2].touch - _y[1].tft*_y[0].touch)/(_y[1].tft - _y[0].tft);
	
	_scale_x = (_x[1].tft - _x[0].tft)/(_x[1].touch - _x[0].touch);
	_scale_y = (_y[1].tft - _y[0].tft)/(_y[1].touch - _y[0].touch);
}

bool TFTCalibrator::update()
{
	if(_calibration_pair_counter < _calibration_pair_goal){
		//retrieve a point from the touch screen
		TSPoint p = _touch.getPoint();
		
		//check if the point is different from the previous point. If not: skip it.
		if((_calibration_pair_counter>0) && (NORM2(p.x - _x[_calibration_pair_counter-1].touch) + NORM2(p.y - _y[_calibration_pair_counter-1].touch)) < 400){
			return false;
		}
		
		if((p.z > 10) && (p.z < 1000)){
			//we retrieved an actual touch
			addCalibrationPoint(p);
			if(_calibration_pair_counter == _calibration_pair_goal){
				finishCalibration();
				return true;
			} else {
				drawNextCalibrationPoint();
			}
		}
	}
	
	return false;
}

void TFTCalibrator::addCalibrationPoint(TSPoint p)
{
	_x[_calibration_pair_counter].touch = p.x;
	_y[_calibration_pair_counter].touch = p.y;
	_calibration_pair_counter++;
}

void TFTCalibrator::drawNextCalibrationPoint()
{
	switch(_calibration_pair_counter){
		case 0: drawCalibrationPoint(_tft.width()*0.1, _tft.height()*0.1); break;
		case 1: drawCalibrationPoint(_tft.width()*0.9, _tft.height()*0.9); break;
		case 2: drawCalibrationPoint(_tft.width()*0.9, _tft.height()*0.1); break;
		case 3: drawCalibrationPoint(_tft.width()*0.1, _tft.height()*0.9); break;
	}
}
