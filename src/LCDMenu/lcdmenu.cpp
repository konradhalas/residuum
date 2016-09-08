#ifndef UNIT_TEST

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "lcdmenu.h"

void LCDMenuRenderer::setup(int lcdLedPin) {
  pinMode(lcdLedPin, OUTPUT);
  analogWrite(lcdLedPin, 255);
  display.begin();
  display.setContrast(60);
}

void LCDMenuRenderer::renderStart() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
}

void LCDMenuRenderer::renderItem(const MenuItem &item, bool isSelected) {
    display.println((isSelected ? ">" : " ") + item.getName() + " = " + item.getValue());
}

void LCDMenuRenderer::renderFinish() {
  display.display();
}

ArduinoMenuActionsProvider::ArduinoMenuActionsProvider(int firstButton, int secondButton, int buttonsDealy) {
  this->firstButton = firstButton;
  this->secondButton = secondButton;
  this->buttonsDealy = buttonsDealy;
  pinMode(firstButton, INPUT);
  pinMode(secondButton, INPUT);
}

bool ArduinoMenuActionsProvider::isToggleModeAction() {
  return digitalRead(this->secondButton) == HIGH;
};

bool ArduinoMenuActionsProvider::isNextAction() {
  return digitalRead(this->firstButton) == HIGH;
};

void ArduinoMenuActionsProvider::afterActionHandler() {
  delay(this->buttonsDealy);
};

#endif
