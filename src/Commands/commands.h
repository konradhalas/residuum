#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <QTRSensors.h>

#include "Follower/drv8835motorsdriver.h"
#include "Follower/qtrlinedetector.h"
#include "consts.h"
#include "menu.h"
#include "settings.h"
#include "storage.h"
#define SAVE_SETTINGS(attr, value) {                                                  \
                                      Settings settings = Storage<Settings>::load();  \
                                      settings.attr = value;                          \
                                      Storage<Settings>::save(settings);              \
                                   }

class ChangeContrastCommand: public Command<IntegerValueMenuItem> {
  public:
    ChangeContrastCommand(Adafruit_PCD8544 &display): display(display) {
    }
    void run(IntegerValueMenuItem &item) {
        display.setContrast(item.getValue());
        SAVE_SETTINGS(lcdContrast, item.getValue());
    }
  private:
    Adafruit_PCD8544 &display;
};

class ToggleBacklightCommand: public Command<BoolValueMenuItem> {
  public:
    ToggleBacklightCommand(int pin): pin(pin) {}
    void run(BoolValueMenuItem &item) {
        analogWrite(this->pin, item.getValue() ? 255 : 0);
        SAVE_SETTINGS(lcdBakclight, item.getValue());
    }
  private:
    int pin;
};

class ReadReflectanceSensorCommand: public Command<IntegerValueMenuItem> {
  public:
    ReadReflectanceSensorCommand(QTRSensorsRC &qtr, int sensorNumber): qtr(qtr), sensorNumber(sensorNumber) {}
    void run(IntegerValueMenuItem &item) {
      unsigned int sensorValues[NUMBER_OF_REFLECTANT_SENSORS];
      this->qtr.read(sensorValues);
      item.setValue(sensorValues[this->sensorNumber - 1]);
    }
  private:
    QTRSensorsRC &qtr;
    int sensorNumber;
};

class CalibrateCommand: public Command<ActionMenuItem> {
  public:
  CalibrateCommand(QTRSensorsRC &qtr): qtr(qtr) {}
  void run(ActionMenuItem &item) {
    for (int i = 0; i < 400; i++) {
      this->qtr.calibrate();
    }
  }
  private:
    QTRSensorsRC &qtr;
};

class ReadLineCommand: public Command<IntegerValueMenuItem> {
  public:
    ReadLineCommand(QtrLineDetector &lineDetector): lineDetector(lineDetector) {}
    void run(IntegerValueMenuItem &item) {
      item.setValue(this->lineDetector.detectLine());
    }
  private:
    QtrLineDetector &lineDetector;
};

class MotorCheckCommand: public Command<ActionMenuItem> {
  public:
    MotorCheckCommand(DRV8835MotorsDriver &motorsDriver, int motor, int speed): motorsDriver(motorsDriver), motor(motor), speed(speed) {}
    void run(ActionMenuItem &item) {
      if (this->motor == MOTOR_LEFT || this->motor == MOTOR_BOTH) {
        this->motorsDriver.setLeftMotorSpeed(this->speed);
      }
      if (this->motor == MOTOR_RIGHT || this->motor == MOTOR_BOTH) {
        this->motorsDriver.setRightMotorSpeed(this->speed);
      }
      delay(2000);
      if (this->motor == MOTOR_LEFT || this->motor == MOTOR_BOTH) {
        this->motorsDriver.setLeftMotorSpeed(0);
      }
      if (this->motor == MOTOR_RIGHT || this->motor == MOTOR_BOTH) {
        this->motorsDriver.setRightMotorSpeed(0);
      }
    }
  private:
    DRV8835MotorsDriver &motorsDriver;
    int motor;
    int speed;
};

class FollowCommand: public Command<ActionMenuItem> {
  public:
    FollowCommand(LineDetector &lineDetector, MotorsDriver &motorsDriver, int stopButtonPin, unsigned long timeout): lineDetector(lineDetector), motorsDriver(motorsDriver), stopButtonPin(stopButtonPin), timeout(timeout) {}
    void run(ActionMenuItem &item) {
      Settings settigns = Storage<Settings>::load();
      Follower follower = Follower(this->lineDetector, this->motorsDriver, settigns.followerKp, settigns.followerKd);
      unsigned long startTime = millis();
      while (digitalRead(this->stopButtonPin) == HIGH || (millis() - startTime) < timeout) {
        follower.follow();
      }
      follower.finish();
    }
  private:
    LineDetector &lineDetector;
    MotorsDriver &motorsDriver;
    int stopButtonPin;
    unsigned long timeout;
};

class UpdateFollowerKpCommand: public Command<FloatValueMenuItem> {
  public:
    UpdateFollowerKpCommand(){}
    void run(FloatValueMenuItem &item) {
      SAVE_SETTINGS(followerKp, item.getValue());
    }
};

class UpdateFollowerKdCommand: public Command<IntegerValueMenuItem> {
  public:
    UpdateFollowerKdCommand(){}
    void run(IntegerValueMenuItem &item) {
      SAVE_SETTINGS(followerKd, item.getValue());
    }
};

#endif
