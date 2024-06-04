#include "Buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer(int pin) {
  this->pin = pin;
}

void Buzzer::slowBeep() {
    onDurationMs = 100;
    offDurationMs = 2000;
    toneFrequency = 500;
}

void Buzzer::fastBeep() {
    onDurationMs = 200;
    offDurationMs = 200;
    toneFrequency = 1000;
}

void Buzzer::longBeep() {
    onDurationMs = 1000;
    offDurationMs = 1000;
    toneFrequency = 500;
}

void Buzzer::noBeep() {
    onDurationMs = 0;
    offDurationMs = 1;
}

void Buzzer::beep(int onDurationMs, int offDurationMs, int tone) {
    this->onDurationMs = onDurationMs;
    this->offDurationMs = offDurationMs;
    this->toneFrequency = tone;
}

void Buzzer::update() {
    int time = millis() % (onDurationMs + offDurationMs);
    if (time < onDurationMs) {
        tone(pin, toneFrequency); //1000 sounds like error
    } else {
        noTone(pin);
    }
}