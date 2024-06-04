#ifndef LPS22_H
#define LPS22_H

#include <Adafruit_Sensor.h>
#include <Adafruit_LPS2X.h>

class LPS22 {
  public:
    LPS22();
    bool begin();
    float readPressure();
    float readTemperature();
    float readAltitude();
    void setDataRate(lps22_rate_t rate);
    lps22_rate_t getDataRate();

  private:
    Adafruit_LPS22 lps;
    float getAltitude(float pressure, float temperature);
};

#endif