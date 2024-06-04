#include "LPS22.h"

LPS22::LPS22() {
}

bool LPS22::begin() {
  return lps.begin_I2C(0x5c);
}

float LPS22::getAltitude(float pressure, float temperature) {
  float seaLevelPressure = 1013.25; // sea level pressure in hPa
  float altitude = 44330.0 * (1.0 - pow(pressure / seaLevelPressure, 0.1903));
  altitude += (temperature - 15.0) / 5.0; // adjust for temperature
  return altitude;
}

float LPS22::readPressure() {
  sensors_event_t temp;
  sensors_event_t pressure;
  lps.getEvent(&pressure, &temp);// get pressure
  return pressure.pressure;
}

float LPS22::readTemperature() {
  sensors_event_t temp;
  sensors_event_t pressure;
  lps.getEvent(&pressure, &temp);// get pressure
    return temp.temperature;
}

float LPS22::readAltitude() {
  sensors_event_t temp;
  sensors_event_t pressure;
  lps.getEvent(&pressure, &temp);// get pressure
  return getAltitude(pressure.pressure, temp.temperature);
}

void LPS22::setDataRate(lps22_rate_t rate) {
  lps.setDataRate(rate);
}

lps22_rate_t LPS22::getDataRate() {
  return lps.getDataRate();
}