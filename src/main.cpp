#ifndef UNIT_TEST

#include <SPI.h>
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
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider(NEXT_BUTTON_PIN, EDIT_BUTTON_PIN, PREVIOUS_BUTTON_PIN, BUTTONS_DELAY);
Menu menu = Menu(renderer, actionsProvider, HANDLE_TICK_FREQUENCY);

QTRSensorsRC qtr = QTRSensorsRC((unsigned char[]) {RS_1_PIN, RS_2_PIN, RS_3_PIN, RS_4_PIN, RS_5_PIN, RS_6_PIN, RS_7_PIN,RS_8_PIN}, NUMBER_OF_REFLECTANT_SENSORS);

DRV8835MotorsDriver motorsDriver = DRV8835MotorsDriver(MOTOR_LEFT_PHASE, MOTOR_LEFT_ENABLE, MOTOR_RIGHT_PHASE, MOTOR_RIGHT_ENABLE, BASE_MOTOR_SPEED);
QtrLineDetector lineDetector = QtrLineDetector(qtr, NUMBER_OF_REFLECTANT_SENSORS);

void setup()   {
  Serial.begin(9600);

  Settings settings;

  if (digitalRead(EDIT_BUTTON_PIN) == HIGH) {
    Storage<Settings>::save(settings);
  } else {
     settings = Storage<Settings>::load();
  }

  renderer.setup(LCD_LED_PIN, settings.lcdContrast, settings.lcdBakclight);

  motorsDriver.setup();

  SubMenuItem *motorsSubMenu = new SubMenuItem("MOTORS", &menu);
  motorsSubMenu->addItem(new ActionMenuItem("LFWD", new MotorCheckCommand(motorsDriver, MOTOR_LEFT, BASE_MOTOR_SPEED)));
  motorsSubMenu->addItem(new ActionMenuItem("LBCK", new MotorCheckCommand(motorsDriver, MOTOR_LEFT, -BASE_MOTOR_SPEED)));
  motorsSubMenu->addItem(new ActionMenuItem("RFWD", new MotorCheckCommand(motorsDriver, MOTOR_RIGHT, BASE_MOTOR_SPEED)));
  motorsSubMenu->addItem(new ActionMenuItem("RBCK", new MotorCheckCommand(motorsDriver, MOTOR_RIGHT, -BASE_MOTOR_SPEED)));
  menu.addItem(motorsSubMenu);

  SubMenuItem *displaySubMenu = new SubMenuItem("DISPLAY", &menu);
  displaySubMenu->addItem(new IntegerValueMenuItem("CON", settings.lcdContrast, new ChangeContrastCommand(display)));
  displaySubMenu->addItem(new BoolValueMenuItem("BCK", settings.lcdBakclight, new ToggleBacklightCommand(LCD_LED_PIN)));
  menu.addItem(displaySubMenu);

  SubMenuItem *lineDetectorSubMenu = new SubMenuItem("SENSORS", &menu);
  lineDetectorSubMenu->addItem(new IntegerValueMenuItem("L", 0, NULL, new ReadLineCommand(lineDetector)));
  for (int i = 1; i <= NUMBER_OF_REFLECTANT_SENSORS; i++) {
    lineDetectorSubMenu->addItem(new IntegerValueMenuItem("S" + String(i), 0, NULL, new ReadReflectanceSensorCommand(qtr, i)));
  }
  menu.addItem(lineDetectorSubMenu);

  SubMenuItem *followerSubMenu = new SubMenuItem("FOLLOWER", &menu);
  followerSubMenu->addItem(new FloatValueMenuItem("KP", settings.followerKp, FOLLOWER_KP_BASE, new UpdateFollowerKpCommand()));
  followerSubMenu->addItem(new IntegerValueMenuItem("KD", settings.followerKd, new UpdateFollowerKdCommand()));
  followerSubMenu->addItem(new ActionMenuItem("CALIB", new CalibrateCommand(qtr)));
  followerSubMenu->addItem(new ActionMenuItem("FOLLOW", new FollowCommand(lineDetector, motorsDriver, EDIT_BUTTON_PIN, FOLLOW_TIMEOUT)));
  menu.addItem(followerSubMenu);
}

void loop() {
  menu.handle();
}

#endif
