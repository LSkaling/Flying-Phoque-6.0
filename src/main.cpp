#include <Arduino.h>
#include <Wire.h>
#include "PinDefinitions.h"
#include "StatusIndicator.h"
#include "HallEffect.h"
#include "Buzzer.h"
#include "ADXL345.h"
#include "LPS22.h"
#include "Igniter.h"
#include <SD.h>


HallEffect hallEffect(PinDefs.HALL_EFFECT);

StatusIndicator statusIndicator(PinDefs.STATUS_LED_RED, PinDefs.STATUS_LED_GREEN, PinDefs.STATUS_LED_BLUE);

ADXL345 accel;

Buzzer buzzer(PinDefs.BUZZER);

LPS22 lps;

Igniter igniter(PinDefs.IGNITER, PinDefs.IGNITER_SENSE);

const int chipSelect = BUILTIN_SDCARD;
File logFile;

String getNextLogFileName() {
  int fileNumber = 1;
  String fileName;
  while (true) {
    fileName = "flight_log_" + String(fileNumber) + ".txt";
    if (!SD.exists(fileName.c_str())) {
      break;
    }
    fileNumber++;
  }
  return fileName;
}
void setup() {
  Serial.begin(9600);
  PinDefs.setupPins();

  statusIndicator.setIntensity(1, 0.15, 0.15);
  statusIndicator.solid(StatusIndicator::BLUE);

  //buzzer.slowBeep();

  Serial.println("Accel Init");
  accel.begin();

  Serial.println("LPS Init");
  lps.begin();

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // Get the next log file name
  String logFileName = getNextLogFileName();
  Serial.print("Creating log file: ");
  Serial.println(logFileName);

  logFile = SD.open(logFileName.c_str(), FILE_WRITE);
  if (!logFile) {
    Serial.println("Error opening log file.");
    return;
  }

  logFile.println("Flight Log Start");
  logFile.println("Time\tX\tY\tZ\tAltitude");
  logFile.flush();
  
  Serial.println("Setup done");

  lps.setDataRate(LPS22_RATE_10_HZ);

  // Print to Serial Monitor
  Serial.println("Recording Finished!");

  

  igniter.arm();

}

void loop() {
  //print out time
  Serial.print(millis()); Serial.print(" ");
  logFile.print(millis()); logFile.print("\t");

  //print out the acceleration data
  sensors_event_t event = accel.getEvent();
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.print("m/s^2 ");
  logFile.print(event.acceleration.x); logFile.print("\t");
  logFile.print(event.acceleration.y); logFile.print("\t");
  logFile.print(event.acceleration.z); logFile.print("\t");
  
  //print out the altitude data
  float altitude = lps.readAltitude();
  Serial.print("\tAltitude: "); Serial.print(altitude); Serial.println("m");
  logFile.print(altitude); logFile.print("\t");

  logFile.println();
  logFile.flush();
  
  statusIndicator.update();
  buzzer.update();
}
