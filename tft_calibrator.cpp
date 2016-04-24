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
	
	//_tft->setRotation(0);
	drawNextCalibrationPoint();
}

void TFTCalibrator::drawCalibrationPoint(uint16_t x, uint16_t y)
{
	_x[_calibration_pair_counter].tft = x;
	_y[_calibration_pair_counter].tft = y;
	
	//pinMode(A2,OUTPUT);
	//pinMode(A3,OUTPUT);
	_tft.fillScreen(0x0000);
	_tft.fillCircle(x,y,4,0xFFFF);
	
	Serial.print("Point drawn at: "); Serial.print(x); Serial.print(", "); Serial.println(y);
}

void TFTCalibrator::finishCalibration()
{
	
	/*Serial.print("_x[0].tft"); Serial.println(_x[0].tft);
	Serial.print("_x[1].tft"); Serial.println(_x[1].tft);
	Serial.print("_y[0].tft"); Serial.println(_y[0].tft);
	Serial.print("_y[1].tft"); Serial.println(_y[1].tft);
	
	Serial.print("_x[0].touch"); Serial.println(_x[0].touch);
	Serial.print("_x[1].touch"); Serial.println(_x[1].touch);
	Serial.print("_y[0].touch"); Serial.println(_y[0].touch);
	Serial.print("_y[1].touch"); Serial.println(_y[1].touch);*/

	_offset_x = (_x[0].tft*_x[1].touch - _x[1].tft*_x[0].touch)/(_x[1].tft - _x[0].tft);
	_offset_y = (_y[0].tft*_y[1].touch - _y[1].tft*_y[0].touch)/(_y[1].tft - _y[0].tft);
	
	_scale_x = ((float)_x[1].tft - _x[0].tft)/((float)_x[1].touch - _x[0].touch);
	_scale_y = ((float)_y[1].tft - _y[0].tft)/((float)_y[1].touch - _y[0].touch);
	
	Serial.print("Offset X: "); Serial.println(_offset_x);
	Serial.print("Offset Y: "); Serial.println(_offset_y);
	Serial.print("Scale X: "); Serial.println(_scale_x);
	Serial.print("Scale Y: "); Serial.println(_scale_y);
}

bool TFTCalibrator::update()
{
	if(_calibration_pair_counter < _calibration_pair_goal){
		//retrieve a point from the touch screen
		TSPoint p = _touch.getPoint();
		_tft.getControl();
		
		if((p.z > 10) && (p.z < 1000)){
			Serial.println("Touch");
		
			//check if the point is different from the previous point. If not: skip it.
			if((_calibration_pair_counter==0) || 
			   ((_calibration_pair_counter>0) && (NORM2(p.x - _x[_calibration_pair_counter-1].touch) + NORM2(p.y - _y[_calibration_pair_counter-1].touch)) > 10000)){
				//we retrieved a new touch
				addCalibrationPoint(p);
				Serial.println("Calibration point added.");
				if(_calibration_pair_counter == _calibration_pair_goal){
					finishCalibration();
					Serial.println("Calibration finished");
					return true;
				} else {
					drawNextCalibrationPoint();
					Serial.println("Draw next calibration point");
				}
			}
		}
	}
	
	return false;
}

/*bool TFTCalibrator::updateSimple()
{
		//retrieve a point from the touch screen
		TSPoint p = _touch.getPoint();
		_tft.getControl(); //return control to the tft screen
		
		if((p.z > 10) && (p.z < 1000)){
			Serial.println("Touch");
		
			//check if the point is different from the previous point. If not: skip it.
			if((_calibration_pair_counter==0) || 
			   ((_calibration_pair_counter>0) && (NORM2(p.x - _x[_calibration_pair_counter-1].touch) + NORM2(p.y - _y[_calibration_pair_counter-1].touch)) > 10000)){
				//we retrieved a new touch
				_calibration_pair_counter++;
				drawNextCalibrationPoint();
			}
		}
	
	return false;
}*/

void TFTCalibrator::addCalibrationPoint(TSPoint p)
{
	_x[_calibration_pair_counter].touch = p.x;
	_y[_calibration_pair_counter].touch = p.y;
	_calibration_pair_counter++;
}

void TFTCalibrator::drawNextCalibrationPoint()
{
	Serial.print("pair counter: "); Serial.println(_calibration_pair_counter);
	
	switch(_calibration_pair_counter){
		case 0: drawCalibrationPoint(_tft.width()*0.1, _tft.height()*0.1); break;
		case 1: drawCalibrationPoint(_tft.width()*0.9, _tft.height()*0.9); break;
		case 2: drawCalibrationPoint(_tft.width()*0.9, _tft.height()*0.1); break;
		case 3: drawCalibrationPoint(_tft.width()*0.1, _tft.height()*0.9); break;
	}
}

int16_t TFTCalibrator::offsetX()
{
	return _offset_x;
}

int16_t TFTCalibrator::offsetY()
{
	return _offset_y;
}

float TFTCalibrator::scaleX()
{
	return _scale_x;
}

float TFTCalibrator::scaleY()
{
	return _scale_y;
}
