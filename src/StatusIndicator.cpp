#include "StatusIndicator.h"
#include <Arduino.h>

StatusIndicator::StatusIndicator(int redPin, int greenPin, int bluePin) {
  this->redPin = redPin;
  this->greenPin = greenPin;
  this->bluePin = bluePin;
  redIntensity = 1;
  greenIntensity = 1;
  blueIntensity = 1;
  currentColor = OFF;
  MAX_INTENSITY = 16;
}

void StatusIndicator::flash(Color color, int onDurationMs, int offDurationMs) {
  this->onDurationMs = onDurationMs;
  this->offDurationMs = offDurationMs;
  currentColor = color;
  switch (color) {
    case RED:
      redPower = MAX_INTENSITY;
      greenPower = 0;
      bluePower = 0;
      break;
    case GREEN:
      redPower = 0;
      greenPower = MAX_INTENSITY;
      bluePower = 0;
      break;
    case BLUE:
      redPower = 0;
      greenPower = 0;
      bluePower = MAX_INTENSITY;
      break;
    case ORANGE:
      redPower = MAX_INTENSITY;
      greenPower = MAX_INTENSITY / 2;
      bluePower = 0;
      break;
    case WHITE:
      redPower = MAX_INTENSITY;
      greenPower = MAX_INTENSITY;
      bluePower = MAX_INTENSITY;
      break;
    default:
      break;
  }
}

void StatusIndicator::solid(Color color) {
  onDurationMs = 1;
  offDurationMs = 0;
  currentColor = color;
  switch (color) {
    case RED:
      redPower = MAX_INTENSITY;
      greenPower = 0;
      bluePower = 0;
      break;
    case GREEN:
      redPower = 0;
      greenPower = MAX_INTENSITY;
      bluePower = 0;
      break;
    case BLUE:
      redPower = 0;
      greenPower = 0;
      bluePower = MAX_INTENSITY;
      break;
    case ORANGE:
      redPower = MAX_INTENSITY;
      greenPower = MAX_INTENSITY / 2;
      bluePower = 0;
      break;
    case WHITE:
      redPower = MAX_INTENSITY;
      greenPower = MAX_INTENSITY;
      bluePower = MAX_INTENSITY;
      break;
    default:
      break;
  }
}

void StatusIndicator::off() {
  currentColor = OFF;
  redPower = 0;
  greenPower = 0;
  bluePower = 0;
}

void StatusIndicator::update() {
  int cycleTime = millis() % (onDurationMs + offDurationMs);
  if (cycleTime < onDurationMs) { //on
    int time = millis() % MAX_INTENSITY;
    digitalWrite(redPin, time < redPower * redIntensity ? LOW : HIGH);
    digitalWrite(greenPin, time < greenPower * greenIntensity ? LOW : HIGH);
    digitalWrite(bluePin, time < bluePower * blueIntensity ? LOW : HIGH);
  } else { //off
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  }



}

void StatusIndicator::setIntensity(float redIntensity, float greenIntensity, float blueIntensity) {
  this->redIntensity = redIntensity;
  this->greenIntensity = greenIntensity;
  this->blueIntensity = blueIntensity;
}