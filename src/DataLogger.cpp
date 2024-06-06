#include "DataLogger.h"
#include <SD.h>
#include <vector>
#include <functional>

DataLogger::DataLogger(int chipSelectPin, bool useSerialMonitor, std::vector<Variable> vars)
    : csPin(chipSelectPin), serialMonitor(useSerialMonitor), variables(vars) {}

bool DataLogger::begin() {
    if (!SD.begin(csPin)) {
        return false;
    }

    String fileName = getNextLogFileName(); 
    logFile = SD.open(fileName.c_str(), FILE_WRITE);
    if (!logFile) {
        return false;
    }
    logFile.println("Data Logger Initialized");

    //print the header
    String header;
    for (const auto& variable : variables) {
        header += variable.name + "\t";
    }
    logFile.println(header);
    logFile.flush(); // Ensure data is written to the SD card

    return true;
}

bool DataLogger::logData() {
    if (!logFile) {
        return false;
    }

    String dataLine;
    for (const auto& variable : variables) {
        float value = variable.getter();
        dataLine += String(value) + "\t";
        if (serialMonitor) {
            Serial.print(variable.name + ": " + String(value) + " ");
        }
    }
    logFile.println(dataLine);
    logFile.flush(); // Ensure data is written to the SD card

    if (serialMonitor) {
        Serial.println();
    }
    return true;
}

String DataLogger::getNextLogFileName() {
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