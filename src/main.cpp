#ifndef UNIT_TEST

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "LCDMenu/lcdmenu.h"

#define FIRST_BUTTON_PIN 7
#define SECOND_BUTTON_PIN 13

#define LCD_LED_PIN 5
#define LCD_DC_PIN 8
#define LCD_CS_PIN 10
#define LCD_RST_PIN 9

#define BUTTONS_DELAY 500

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
LCDMenuRenderer renderer = LCDMenuRenderer(display);
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider(FIRST_BUTTON_PIN, SECOND_BUTTON_PIN, BUTTONS_DELAY);
Menu menu = Menu(renderer, actionsProvider);

void setup()   {
  Serial.begin(9600);

  renderer.setup(LCD_LED_PIN);
  menu.addItem(new IntegerValueMenuItem("VAL 1", 10));
  menu.addItem(new IntegerValueMenuItem("VAL 2", 20));
  menu.addItem(new IntegerValueMenuItem("VAL 3", 100));
  menu.addItem(new IntegerValueMenuItem("VAL 4", 200));
  menu.addItem(new IntegerValueMenuItem("VAL 5", 300));
  menu.addItem(new IntegerValueMenuItem("VAL 6", 100));
  menu.addItem(new IntegerValueMenuItem("VAL 7", 10));
  menu.addItem(new IntegerValueMenuItem("VAL 8", 20));
  menu.addItem(new IntegerValueMenuItem("VAL 9", 100));
  menu.addItem(new IntegerValueMenuItem("VAL 10", 200));
  menu.addItem(new IntegerValueMenuItem("VAL 11", 300));
  menu.addItem(new IntegerValueMenuItem("VAL 12", 100));
  menu.addItem(new IntegerValueMenuItem("VAL 13", 300));
  menu.addItem(new IntegerValueMenuItem("VAL 12", 100));
  menu.addItem(new ActionMenuItem("START", NULL));
  menu.render();
}

void loop() {
  menu.handle();
}

#endif
