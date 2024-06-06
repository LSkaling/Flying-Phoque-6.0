#include <Arduino.h>
#include <Wire.h>
#include "PinDefinitions.h"
#include "StatusIndicator.h"
#include "HallEffect.h"
#include "Buzzer.h"
#include "ADXL345.h"
#include "LPS22.h"
#include "Igniter.h"
#include "Feedback.h"
#include "DataLogger.h"
#include <vector>
#include <functional>


HallEffect hallEffect(PinDefs.HALL_EFFECT);

StatusIndicator statusIndicator(PinDefs.STATUS_LED_RED, PinDefs.STATUS_LED_GREEN, PinDefs.STATUS_LED_BLUE);
Buzzer buzzer(PinDefs.BUZZER);
Feedback feedback(statusIndicator, buzzer);

ADXL345 accel;
sensors_event_t event;
float altitude;
float accel_x;
float accel_y;
float accel_z;
int time_ms;

LPS22 lps;


std::vector<DataLogger::Variable> variables = {
    {"time", []() { return time_ms; }},
    {"altitude", []() { return altitude; }},
    {"x_accel", []() { return accel_x; }},
    {"y_accel", []() { return accel_y; }},
    {"z_accel", []() { return accel_z; }}
};

DataLogger dataLogger(PinDefs.SD_CS, true, variables);



void setup() {
  Serial.begin(115200);
  PinDefs.setupPins();

  feedback.setStatus(IDLE);

  if(!dataLogger.begin()) {
    feedback.setStatus(FAILURE);
  }

  if(!accel.begin()) {
    feedback.setStatus(FAILURE);
  }

  if(!lps.begin()) {
    feedback.setStatus(FAILURE);
  }
  lps.setDataRate(LPS22_RATE_10_HZ);

  if(feedback.currentStatus != FAILURE) {
    feedback.setStatus(ARMED);
  }

}

void loop() {
  //print out the acceleration data
  sensors_event_t event = accel.getEvent();
  accel_x = event.acceleration.x;
  accel_y = event.acceleration.y;
  accel_z = event.acceleration.z;
  time_ms = millis();
  altitude = lps.readAltitude();
  if(!dataLogger.logData()){ //Occurs if unplugged TODO: Why didn't this change states?
    feedback.setStatus(FAILURE);}
  feedback.update();
}
