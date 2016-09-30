#ifndef UNIT_TEST

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <QTRSensors.h>

#include "consts.h"
#include "Menu/lcdmenu.h"
#include "Commands/commands.h"
#include "Follower/drv8835motorsdriver.h"

#include "follower.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
LCDMenuRenderer renderer = LCDMenuRenderer(display);
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider(NEXT_BUTTON_PIN, EDIT_BUTTON_PIN, PREVIOUS_BUTTON_PIN, BUTTONS_DELAY);
Menu menu = Menu(renderer, actionsProvider, HANDLE_TICK_FREQUENCY);

QTRSensorsRC qtr = QTRSensorsRC((unsigned char[]) {RS_1_PIN, RS_2_PIN, RS_3_PIN, RS_4_PIN, RS_5_PIN, RS_6_PIN, RS_7_PIN,RS_8_PIN}, NUMBER_OF_REFLECTANT_SENSORS);

DRV8835MotorsDriver motorsDriver = DRV8835MotorsDriver(MOTOR_LEFT_PHASE, MOTOR_LEFT_ENABLE, MOTOR_RIGHT_PHASE, MOTOR_RIGHT_ENABLE);

void setup()   {
  Serial.begin(9600);

  renderer.setup(LCD_LED_PIN, LCD_CONTRAST);

  motorsDriver.setup();

  menu.addItem(new ActionMenuItem("ML FWD", new MotorCheckCommand(motorsDriver, MOTOR_LEFT, 100)));
  menu.addItem(new ActionMenuItem("ML BCK", new MotorCheckCommand(motorsDriver, MOTOR_LEFT, -100)));
  menu.addItem(new ActionMenuItem("MR FWD", new MotorCheckCommand(motorsDriver, MOTOR_RIGHT, 100)));
  menu.addItem(new ActionMenuItem("MR BCK", new MotorCheckCommand(motorsDriver, MOTOR_RIGHT, -100)));

  menu.addItem(new IntegerValueMenuItem("CONTR", LCD_CONTRAST, new ChangeContrastCommand(display)));
  menu.addItem(new BoolValueMenuItem("BCKLI", true, new ToggleBacklightCommand(LCD_LED_PIN)));
  menu.addItem(new IntegerValueMenuItem("LINE", 0, NULL, new ReadLineCommand(qtr)));
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
