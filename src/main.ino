#ifndef UNIT_TEST

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "menu.h"

#define LCD_LED_PIN 5
#define FIRST_BUTTON_PIN 7
#define SECOND_BUTTON_PIN 13
#define LED_PIN 11

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 10, 9);

Menu menu = Menu(display, FIRST_BUTTON_PIN, SECOND_BUTTON_PIN);

void initializeDisplay() {
  pinMode(LCD_LED_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  analogWrite(LCD_LED_PIN, 255);

  display.begin();
  display.setContrast(60);
}

void setup()   {
  Serial.begin(9600);

  initializeDisplay();

  menu.addItem("VAL A", 10);
  menu.addItem("VAL B", 20);
  menu.addItem("VALUE C", 100);
  menu.render();
}

void loop() {
  menu.handle();
}

#endif
