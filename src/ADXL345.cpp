#include "ADXL345.h"

ADXL345::ADXL345() {
  accel = Adafruit_ADXL345_Unified(12345);
}

bool ADXL345::begin() {
  return accel.begin();
  accel.setRange(ADXL345_RANGE_16_G);
}

sensors_event_t ADXL345::getEvent() {
  sensors_event_t event;
  accel.getEvent(&event);
  return event;
}