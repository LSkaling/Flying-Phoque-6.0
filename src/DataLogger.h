#ifndef DATALOGGER_H
#define DATALOGGER_H
#include <map>
#include <vector>
#include <functional>
#include <SD.h>

class DataLogger {
    public:
        struct Variable {
            String name;
            std::function<float()> getter;
        };

        DataLogger(int chipSelectPin, bool useSerialMonitor, std::vector<Variable> variables);
        bool begin();
        bool logData();

    private:
        int csPin;
        bool serialMonitor;
        File logFile;
        std::vector<Variable> variables;
        String getNextLogFileName();
    };

#endif