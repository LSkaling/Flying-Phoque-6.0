#include "HallEffect.h"

HallEffect::HallEffect(int sensorPin) {
  this->sensorPin = sensorPin;
  pinMode(sensorPin, INPUT);
}

bool HallEffect::isMagnetDetected() {
  return digitalRead(sensorPin) == HIGH;
}

int HallEffect::read() {
  return analogRead(sensorPin);
}