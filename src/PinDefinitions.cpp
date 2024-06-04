#include "PinDefinitions.h"
#include <Arduino.h>

PinDefinitions::PinDefinitions():
    STATUS_LED_RED(35),
    STATUS_LED_GREEN(34),
    STATUS_LED_BLUE(33),

    IGNITER(39),
    // IGNITER_2(5),
    // IGNITER_3(6),

    IGNITER_SENSE(38),
    // IGNITER_SENSE_2(15),
    // IGNITER_SENSE_3(14),

    BUZZER(36),
    HALL_EFFECT(23),

    SERVO_0(24),
    SERVO_1(25),

    HBRIDGE1(28),
    HBRIDGE2(29)
{
    // Constructor
}

void PinDefinitions::setupPins() {
    pinMode(STATUS_LED_RED, OUTPUT);
    pinMode(STATUS_LED_GREEN, OUTPUT);
    pinMode(STATUS_LED_BLUE, OUTPUT);

    pinMode(IGNITER, OUTPUT);
    // pinMode(IGNITER_2, OUTPUT);
    // pinMode(IGNITER_3, OUTPUT);

    pinMode(IGNITER_SENSE, INPUT);
    // pinMode(IGNITER_SENSE_2, INPUT);
    // pinMode(IGNITER_SENSE_3, INPUT);

    pinMode(SERVO_0, OUTPUT);
    pinMode(SERVO_1, OUTPUT);

    pinMode(BUZZER, OUTPUT);
    pinMode(HALL_EFFECT, INPUT);

    pinMode(HBRIDGE1, OUTPUT);
    pinMode(HBRIDGE2, OUTPUT);

}

PinDefinitions PinDefs;