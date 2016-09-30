#ifndef UNIT_TEST

#include <Arduino.h>

#include "arduinoactionsprovider.h"

ArduinoMenuActionsProvider::ArduinoMenuActionsProvider(int nextButton, int editButton, int previousButton, int buttonsDealy) {
  this->nextButton = nextButton;
  this->editButton = editButton;
  this->previousButton = previousButton;
  this->buttonsDealy = buttonsDealy;
  pinMode(nextButton, INPUT);
  pinMode(editButton, INPUT);
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
  delay(this->buttonsDealy);
};

#endif
