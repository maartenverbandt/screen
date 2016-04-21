// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#ifndef _ADAFRUIT_TOUCHSCREEN_H_
#define _ADAFRUIT_TOUCHSCREEN_H_
#include <stdint.h>

class TSPoint {
 public:
  TSPoint(void);
  TSPoint(int16_t x, int16_t y, int16_t z);
  
  bool operator==(TSPoint);
  bool operator!=(TSPoint);

  int16_t x, y, z;
};

class TouchScreen {
 public:
  TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);
  TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, Adafruit_GFX &tft);
  TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx, Adafruit_GFX &tft);

  bool isTouching(void);
  uint16_t pressure(void);
  int readTouchY();
  int readTouchX();
  TSPoint getPoint();
  TSPoint getTFTPoint();
  int16_t pressureThreshhold;
  
  void setOffset(int16_t offset_x, int16_t offset_y);
  void setScale(int16_t scale_x, int16_t scale_y);

private:
  uint8_t _yp, _ym, _xm, _xp;
  uint16_t _rxplate;
  Adafruit_GFX &_tft;
  
  int16_t _offset_x, _offset_y;
  float _scale_x, _scale_y;
  TSPoint calibrate(TSPoint p);
};

#endif
