#ifndef UNIT_TEST

#include <Arduino.h>

#include "arduinoactionsprovider.h"

ArduinoMenuActionsProvider::ArduinoMenuActionsProvider(int nextButton, int editButton, int previousButton, int actionLedPin, int buttonsDealy) {
  this->nextButton = nextButton;
  this->editButton = editButton;
  this->previousButton = previousButton;
  this->actionLedPin = actionLedPin;
  this->buttonsDealy = buttonsDealy;
  pinMode(nextButton, INPUT);
  pinMode(editButton, INPUT);
  pinMode(previousButton, INPUT);
  pinMode(actionLedPin, OUTPUT);
}

bool ArduinoMenuActionsProvider::isToggleEditModeAction() {
  return digitalRead(this->editButton) == HIGH;
};

bool ArduinoMenuActionsProvider::isNextAction() {
  return digitalRead(this->nextButton) == HIGH;
};

bool ArduinoMenuActionsProvider::isPreviousAction() {
  return digitalRead(this->previousButton) == HIGH;
};

void ArduinoMenuActionsProvider::afterActionHandler() {
  digitalWrite(this->actionLedPin, HIGH);
  delay(this->buttonsDealy);
  digitalWrite(this->actionLedPin, LOW);
};

#endif
