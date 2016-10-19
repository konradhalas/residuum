#ifndef UNIT_TEST

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <QTRSensors.h>

#include <menu.h>
#include <follower.h>
#include <storage.h>

#include "consts.h"
#include "settings.h"
#include "Commands/commands.h"
#include "Menu/pcd8544renderer.h"
#include "Menu/arduinoactionsprovider.h"
#include "Follower/drv8835motorsdriver.h"
#include "Follower/qtrlinedetector.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
PCD8544MenuRenderer renderer = PCD8544MenuRenderer(display);
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider(NEXT_BUTTON_PIN, EDIT_BUTTON_PIN, PREVIOUS_BUTTON_PIN, STATUS_LED_PIN, BUTTONS_DELAY);
Menu menu = Menu(renderer, actionsProvider, HANDLE_TICK_FREQUENCY);

QTRSensorsRC qtr = QTRSensorsRC((unsigned char[]) {RS_1_PIN, RS_2_PIN, RS_3_PIN, RS_4_PIN, RS_5_PIN, RS_6_PIN, RS_7_PIN,RS_8_PIN}, NUMBER_OF_REFLECTANT_SENSORS);

DRV8835MotorsDriver motorsDriver = DRV8835MotorsDriver(MOTOR_LEFT_PHASE, MOTOR_LEFT_ENABLE, MOTOR_RIGHT_PHASE, MOTOR_RIGHT_ENABLE, BASE_MOTOR_SPEED);
QtrLineDetector lineDetector = QtrLineDetector(qtr, NUMBER_OF_REFLECTANT_SENSORS);

void indicateSetupFinish() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, HIGH);
  delay(BUTTONS_DELAY);
  digitalWrite(STATUS_LED_PIN, LOW);
}

void setup()   {
  Settings settings;

  if (digitalRead(EDIT_BUTTON_PIN) == HIGH) {
    Storage<Settings>::save(settings);
  } else {
     settings = Storage<Settings>::load();
  }

  renderer.setup(LCD_LED_PIN, settings.lcdContrast, settings.lcdBakclight);

  motorsDriver.setup();

  menu.addItem(new ActionMenuItem("FL", new FollowCommand(lineDetector, motorsDriver, EDIT_BUTTON_PIN)));
  menu.addItem(new ActionMenuItem("CL", new CalibrateCommand(qtr)));
  menu.addItem(new FloatValueMenuItem("KP", settings.followerKp, FOLLOWER_KP_BASE, new UpdateFollowerKpCommand()));
  menu.addItem(new IntegerValueMenuItem("KD", settings.followerKd, new UpdateFollowerKdCommand()));
  menu.addItem(new IntegerValueMenuItem("BS", settings.motorsBaseSpeed, new UpdateMotorsBaseSpeedCommand()));
  menu.addItem(new IntegerValueMenuItem("LI", 0, NULL, new ReadLineCommand(lineDetector)));
  menu.addItem(new ActionMenuItem("MT", new MotorCheckCommand(motorsDriver, MOTOR_BOTH)));
  menu.addItem(new IntegerValueMenuItem("FT", settings.followTimeout / MS, new UpdateFollowTimeoutCommand()));

  indicateSetupFinish();
}

void loop() {
  menu.handle();
}

#endif
