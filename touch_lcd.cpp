#include <touch_lcd.h>

#define NORM2(x) x*x

TouchLCD::TouchLCD(uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t rs, uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) : 
	Adafruit_TFTLCD(cs, cd, wr, rd, rs), TouchScreen(xp, yp, xm, ym), 
	_cs(cs), 
	_cd(cd), 
	_wr(wr), 
	_rd(rd),
	_rs(rs),
	_xp(xp),
	_yp(yp),
	_xm(xm),
	_ym(ym),
	_calibration_pair_counter(0), 
	_calibration_pair_goal(0),
	_offset_x(0),
	_offset_y(0),
	_scale_x(1.0f),
	_scale_y(1.0f)
{
	
}

void TouchLCD::startCalibration()
{
	_calibration_pair_counter = 0;
	_calibration_pair_goal = 2;
	
	drawNextCalibrationPoint();
}

void TouchLCD::drawCalibrationPoint(uint16_t x, uint16_t y)
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

void TouchLCD::finishCalibration()
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

bool TouchLCD::update()
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

void TouchLCD::addCalibrationPoint(TSPoint p)
{
	_x[_calibration_pair_counter].touch = p.x;
	_y[_calibration_pair_counter].touch = p.y;
	_calibration_pair_counter++;
}

void TouchLCD::drawNextCalibrationPoint()
{	
	switch(_calibration_pair_counter){
		case 0: drawCalibrationPoint(width()*0.1, height()*0.1); break;
		case 1: drawCalibrationPoint(width()*0.9, height()*0.9); break;
		case 2: drawCalibrationPoint(width()*0.9, height()*0.1); break;
		case 3: drawCalibrationPoint(width()*0.1, height()*0.9); break;
	}
}

int16_t TouchLCD::offsetX()
{
	return _offset_x;
}

int16_t TouchLCD::offsetY()
{
	return _offset_y;
}

float TouchLCD::scaleX()
{
	return _scale_x;
}

float TouchLCD::scaleY()
{
	return _scale_y;
}


void TouchLCD::setOffsetX(int16_t offset_x)
{
	_offset_x = offset_x;
}

void TouchLCD::setOffsetY(int16_t offset_y)
{
	_offset_y = offset_y;
}

void TouchLCD::setScaleX(float scale_x)
{
	_scale_x = scale_x;
}

void TouchLCD::setScaleY(float scale_y)
{
	_scale_y = scale_y;
}

TSPoint TouchLCD::getTFTPoint()
{
	TSPoint p = getPoint();
	controlTFT();
	p.x = ((int)p.x + _offset_x)*_scale_x;
	p.y = ((int)p.y + _offset_y)*_scale_y;
	
	uint16_t t;
	switch(getRotation()) {
		case 1:
			t = p.y;
			p.y = height()  - 1 - p.x;
			p.x = t;
			break;
		case 2:
			p.x = width()  - 1 - p.x;
			p.y = height() - 1 - p.y;
			break;
		case 3:
			t = p.y;
			p.y = p.x;
			p.x = width() - 1 - t;
			break;
	}
	
	return p;
}
