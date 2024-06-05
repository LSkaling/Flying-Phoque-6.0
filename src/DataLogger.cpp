#include "DataLogger.h"
#include <SD.h>
#include <vector>
#include <functional>

DataLogger::DataLogger(int chipSelectPin, bool useSerialMonitor, std::vector<Variable> vars)
    : csPin(chipSelectPin), serialMonitor(useSerialMonitor), variables(vars) {}

void DataLogger::begin() {
    if (!SD.begin(csPin)) {
        if (serialMonitor) {
            Serial.println("SD card initialization failed!");
        }
        return;
    }

    logFile = SD.open("datalog.txt", FILE_WRITE);
    if (!logFile) {
        if (serialMonitor) {
            Serial.println("Failed to open datalog file!");
        }
        return;
    }

    if (serialMonitor) {
        Serial.begin(9600);
        while (!Serial) {
            ; // Wait for serial port to connect. Needed for native USB port only
        }
    }
}

void DataLogger::logData() {
    if (!logFile) return;

    String dataLine;
    for (const auto& variable : variables) {
        float value = variable.getter();
        dataLine += variable.name + ": " + String(value) + " ";
        if (serialMonitor) {
            Serial.print(variable.name + ": " + String(value) + " ");
        }
    }
    dataLine += "\n";
    logFile.println(dataLine);
    logFile.flush(); // Ensure data is written to the SD card

    if (serialMonitor) {
        Serial.println();
    }
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