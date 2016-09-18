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
#define LCD_CONTRAST 55

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
LCDMenuRenderer renderer = LCDMenuRenderer(display);
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider(FIRST_BUTTON_PIN, SECOND_BUTTON_PIN, BUTTONS_DELAY);
Menu menu = Menu(renderer, actionsProvider);

void setup()   {
  Serial.begin(9600);
  
  renderer.setup(LCD_LED_PIN, LCD_CONTRAST);

  menu.addItem(new IntegerValueMenuItem("CONTR", LCD_CONTRAST, new ChangeContrastCommand(display)));
  menu.addItem(new BoolValueMenuItem("BCKLI", true, new ToggleBacklightCommand(LCD_LED_PIN)));
  menu.addItem(new ActionMenuItem("START", NULL));
  menu.render();
}

void loop() {
  menu.handle();
}

#endif
