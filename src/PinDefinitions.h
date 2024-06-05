#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H

class PinDefinitions {
public:
    // Constructor
    PinDefinitions();

    // Digital Pins
    const int STATUS_LED_RED;
    const int STATUS_LED_GREEN;
    const int STATUS_LED_BLUE;

    const int IGNITER;
    const int IGNITER_SENSE;

    const int BUZZER;

    const int HALL_EFFECT;

    const int SERVO_0;
    const int SERVO_1;

    const int HBRIDGE1;
    const int HBRIDGE2;

    const int SD_CS;

    void setupPins();
};

extern PinDefinitions PinDefs;

#endif