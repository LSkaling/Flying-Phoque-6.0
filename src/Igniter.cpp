#include "Igniter.h"
#include <Arduino.h>

Igniter::Igniter(int igniterPin, int sensePin) {
  this->igniterPin = igniterPin;
  this->sensePin = sensePin;
  armed = false;
  firing = false;
}

void Igniter::arm() {
  armed = true;
}

void Igniter::disarm() {
  armed = false;
}

void Igniter::fire() {
  if (armed) {
    firing = true;
    digitalWrite(igniterPin, HIGH);
  }
}

bool Igniter::isArmed() {
  return armed;
}

bool Igniter::isFiring() {
  return firing;
}

bool Igniter::igniterCheck() {
  return digitalRead(sensePin) == LOW;
}

int Igniter::readSensePin() {
  return analogRead(sensePin);
}

void Igniter::reset() {
  armed = false;
  firing = false;
  digitalWrite(igniterPin, LOW);
}