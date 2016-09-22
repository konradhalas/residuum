#ifndef UNIT_TEST

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <QTRSensors.h>

#include "LCDMenu/lcdmenu.h"
#include "Commands/commands.h"

#include "follower.h"

#define NEXT_BUTTON_PIN 23 // PF0
#define EDIT_BUTTON_PIN 13 // PC7
#define PREVIOUS_BUTTON_PIN 7 // PE6

#define LCD_LED_PIN 5 // PC6
#define LCD_DC_PIN 8 // PB4
#define LCD_CS_PIN 10 // SCE, PB6
#define LCD_RST_PIN 9 // PB5

#define RS_1_PIN 3  // PD0
#define RS_2_PIN 2  // PD1
#define RS_3_PIN 0  // PD2
#define RS_4_PIN 1  // PD3
#define RS_5_PIN 4  // PD4
#define RS_6_PIN 12 // PD6
#define RS_7_PIN 6  // PD7
#define RS_8_PIN 18 // PF7

#define BUTTONS_DELAY 500
#define LCD_CONTRAST 55
#define NUMBER_OF_REFLECTANT_SENSORS 8

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
LCDMenuRenderer renderer = LCDMenuRenderer(display);
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider(NEXT_BUTTON_PIN, EDIT_BUTTON_PIN, PREVIOUS_BUTTON_PIN, BUTTONS_DELAY);
Menu menu = Menu(renderer, actionsProvider);

QTRSensorsRC qtr = QTRSensorsRC((unsigned char[]) {RS_1_PIN, RS_2_PIN, RS_3_PIN, RS_4_PIN, RS_5_PIN, RS_6_PIN, RS_7_PIN,RS_8_PIN}, NUMBER_OF_REFLECTANT_SENSORS);

void setup()   {
  Serial.begin(9600);

  renderer.setup(LCD_LED_PIN, LCD_CONTRAST);

  menu.addItem(new IntegerValueMenuItem("CONTR", LCD_CONTRAST, new ChangeContrastCommand(display)));
  menu.addItem(new BoolValueMenuItem("BCKLI", true, new ToggleBacklightCommand(LCD_LED_PIN)));
  for (int i = 1; i <= NUMBER_OF_REFLECTANT_SENSORS; i++) {
    menu.addItem(new IntegerValueMenuItem("RS" + String(i), 0, NULL, new ReadReflectanceSensorCommand(qtr, i)));
  }
  menu.addItem(new ActionMenuItem("CALIB", new CalibrateCommand(qtr)));
  menu.addItem(new ActionMenuItem("START", NULL));
  menu.render();
}

void loop() {
  menu.handle();
}

#endif
