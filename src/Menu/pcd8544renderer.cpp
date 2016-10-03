#ifndef UNIT_TEST

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "pcd8544renderer.h"

PCD8544MenuRenderer::PCD8544MenuRenderer(Adafruit_PCD8544 &display): display(display) {
}

void PCD8544MenuRenderer::setup(int lcdLedPin, int contrast) {
  pinMode(lcdLedPin, OUTPUT);
  analogWrite(lcdLedPin, 255);
  display.begin();
  display.setContrast(contrast);
}

void PCD8544MenuRenderer::renderStart(bool isEditMode) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  this->isEditMode = isEditMode;
}

void PCD8544MenuRenderer::renderItem(const IntegerValueMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + item.getName() + " = " + item.getValue());
}

void PCD8544MenuRenderer::renderItem(const BoolValueMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + item.getName() + " = " + (item.getValue() ? "ON" : "OFF"));
}

void PCD8544MenuRenderer::renderItem(const ActionMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + item.getName());
}

void PCD8544MenuRenderer::renderItem(const SubMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + item.getName());
}

void PCD8544MenuRenderer::renderItem(const ParentMenuItem &item, bool isSelected) {
    display.println(this->getItemPrefix(isSelected) + "...");
}

String PCD8544MenuRenderer::getItemPrefix(bool isSelected) {
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

void PCD8544MenuRenderer::renderFinish() {
  display.display();
}

void PCD8544MenuRenderer::renderProgress(const MenuItem &item) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("\n\n\n" + item.getName() + "...");
  display.display();
}

#endif
