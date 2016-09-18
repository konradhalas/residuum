#ifndef UNIT_TEST

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "lcdmenu.h"

LCDMenuRenderer::LCDMenuRenderer(Adafruit_PCD8544 &display): display(display) {
}

void LCDMenuRenderer::setup(int lcdLedPin, int contrast) {
  pinMode(lcdLedPin, OUTPUT);
  analogWrite(lcdLedPin, 255);
  display.begin();
  display.setContrast(contrast);
}

void LCDMenuRenderer::renderStart(bool isEditMode) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  this->isEditMode = isEditMode;
}

void LCDMenuRenderer::renderItem(const IntegerValueMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + item.getName() + " = " + item.getValue());
}

void LCDMenuRenderer::renderItem(const BoolValueMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + item.getName() + " = " + (item.getValue() ? "ON" : "OFF"));
}

void LCDMenuRenderer::renderItem(const ActionMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + item.getName());
}

String LCDMenuRenderer::getItemPrefix(bool isSelected) {
  String prefix = " ";
  if (isSelected) {
    if (this->isEditMode) {
      prefix = '#';
    } else {
      prefix = ">";
    }
  }
  return prefix;
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

bool ArduinoMenuActionsProvider::isToggleEditModeAction() {
  return digitalRead(this->secondButton) == HIGH;
};

bool ArduinoMenuActionsProvider::isNextAction() {
  return digitalRead(this->firstButton) == HIGH;
};

void ArduinoMenuActionsProvider::afterActionHandler() {
  delay(this->buttonsDealy);
};

#endif
