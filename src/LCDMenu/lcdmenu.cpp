#ifndef UNIT_TEST

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "lcdmenu.h"

void LCDMenuRenderer::render(MenuNode *node) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  MenuNode *current = node;
  do {
    MenuItem &item = current->getItem();
    display.println(item.getName() + " = " + item.getValue());
    current = current->getNext();
  } while (current != node);
  display.display();
}

void LCDMenuRenderer::setup(int lcdLedPin) {
  pinMode(lcdLedPin, OUTPUT);
  analogWrite(lcdLedPin, 255);
  display.begin();
  display.setContrast(60);
}

ArduinoMenuActionsProvider::ArduinoMenuActionsProvider(int firstButton, int secondButton, int buttonsDealy) {
  this->firstButton = firstButton;
  this->secondButton = secondButton;
  this->buttonsDealy = buttonsDealy;
  pinMode(firstButton, INPUT);
  pinMode(secondButton, INPUT);
}

bool ArduinoMenuActionsProvider::isSelectAction() {
  return digitalRead(this->secondButton) == HIGH;
};

bool ArduinoMenuActionsProvider::isNextAction() {
  return digitalRead(this->firstButton) == HIGH;
};

void ArduinoMenuActionsProvider::afterActionHandler() {
  delay(this->buttonsDealy);
};

#endif
