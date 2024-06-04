#ifndef ADXL345_H
#define ADXL345_H

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

class ADXL345 {
  public:
    ADXL345();
    bool begin();
    sensors_event_t getEvent();
    

  private:
    Adafruit_ADXL345_Unified accel;
};

#endif