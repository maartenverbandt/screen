#include "SPFD5408.h"

#define NORM2(x) x*x

SPFD5408::SPFD5408() : 
	Adafruit_TFTLCD(SPFD5408_CS, SPFD5408_CD, SPFD5408_WR, SPFD5408_RD, SPFD5408_RESET), TouchScreen(SPFD5408_XP, SPFD5408_YP, SPFD5408_XM, SPFD5408_YM), 
	_cs(SPFD5408_CS), 
	_cd(SPFD5408_CD), 
	_wr(SPFD5408_WR), 
	_rd(SPFD5408_RD),
	_calibration_pair_counter(0), 
	_calibration_pair_goal(0),
	_offset_x(0),
	_offset_y(0),
	_scale_x(0),
	_scale_y(0)
{
	
}

void SPFD5408::controlTFT()
{
	pinMode(_cs, OUTPUT);    // Enable outputs
	pinMode(_cd, OUTPUT);
	pinMode(_wr, OUTPUT);
	pinMode(_rd, OUTPUT);
}

void SPFD5408::startCalibration()
{
	_calibration_pair_counter = 0;
	_calibration_pair_goal = 2;
	
	drawNextCalibrationPoint();
}

void SPFD5408::drawCalibrationPoint(uint16_t x, uint16_t y)
{

	fillScreen(0x0000);
	fillCircle(x,y,4,0xFFFF);

	uint16_t t;
	switch(getRotation()) {
		case 1:
			t = x;
			x = height()  - 1 - y;
			y = t;
			break;
		case 2:
			x = width()  - 1 - x;
			y = height() - 1 - y;
			break;
		case 3:
			t = x;
			x = y;
			y = width() - 1 - t;
			break;
	}

	_x[_calibration_pair_counter].tft = x;
	_y[_calibration_pair_counter].tft = y;
	
	//Serial.print("Point drawn at: "); Serial.print(x); Serial.print(", "); Serial.println(y);
}

void SPFD5408::finishCalibration()
{
	
	/*Serial.print("_x[0].tft"); Serial.println(_x[0].tft);
	Serial.print("_x[1].tft"); Serial.println(_x[1].tft);
	Serial.print("_y[0].tft"); Serial.println(_y[0].tft);
	Serial.print("_y[1].tft"); Serial.println(_y[1].tft);
	
	Serial.print("_x[0].touch"); Serial.println(_x[0].touch);
	Serial.print("_x[1].touch"); Serial.println(_x[1].touch);
	Serial.print("_y[0].touch"); Serial.println(_y[0].touch);
	Serial.print("_y[1].touch"); Serial.println(_y[1].touch);*/

	_offset_x = ((float)_x[0].tft*_x[1].touch - (float)_x[1].tft*_x[0].touch)/((float)_x[1].tft - _x[0].tft);
	_offset_y = ((float)_y[0].tft*_y[1].touch - (float)_y[1].tft*_y[0].touch)/((float)_y[1].tft - _y[0].tft);
	
	_scale_x = ((float)_x[1].tft - _x[0].tft)/((float)_x[1].touch - _x[0].touch);
	_scale_y = ((float)_y[1].tft - _y[0].tft)/((float)_y[1].touch - _y[0].touch);
	
	/*Serial.print("Offset X: "); Serial.println(_offset_x);
	Serial.print("Offset Y: "); Serial.println(_offset_y);
	Serial.print("Scale X: "); Serial.println(_scale_x);
	Serial.print("Scale Y: "); Serial.println(_scale_y);*/
}

bool SPFD5408::update()
{
	if(_calibration_pair_counter < _calibration_pair_goal){
		//retrieve a point from the touch screen
		TSPoint p = getPoint();
		controlTFT();
		
		if((p.z > 10) && (p.z < 1000)){
			//Serial.println("Touch");
		
			//check if the point is different from the previous point. If not: skip it.
			if((_calibration_pair_counter==0) || 
			   ((_calibration_pair_counter>0) && (NORM2(p.x - _x[_calibration_pair_counter-1].touch) + NORM2(p.y - _y[_calibration_pair_counter-1].touch)) > 10000)){
				//we retrieved a new touch
				addCalibrationPoint(p);
				//Serial.println("Calibration point added.");
				if(_calibration_pair_counter == _calibration_pair_goal){
					finishCalibration();
					//Serial.println("Calibration finished");
					return true;
				} else {
					drawNextCalibrationPoint();
					//Serial.println("Draw next calibration point");
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

void SPFD5408::addCalibrationPoint(TSPoint p)
{
	_x[_calibration_pair_counter].touch = p.x;
	_y[_calibration_pair_counter].touch = p.y;
	_calibration_pair_counter++;
}

void SPFD5408::drawNextCalibrationPoint()
{	
	switch(_calibration_pair_counter){
		case 0: drawCalibrationPoint(width()*0.1, height()*0.1); break;
		case 1: drawCalibrationPoint(width()*0.9, height()*0.9); break;
		case 2: drawCalibrationPoint(width()*0.9, height()*0.1); break;
		case 3: drawCalibrationPoint(width()*0.1, height()*0.9); break;
	}
}

int16_t SPFD5408::offsetX()
{
	return _offset_x;
}

int16_t SPFD5408::offsetY()
{
	return _offset_y;
}

float SPFD5408::scaleX()
{
	return _scale_x;
}

float SPFD5408::scaleY()
{
	return _scale_y;
}
