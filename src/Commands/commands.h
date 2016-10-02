#ifndef COMMANDS_H
#define COMMANDS_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <QTRSensors.h>

#include "Follower/drv8835motorsdriver.h"
#include "consts.h"
#include "menu.h"

class ChangeContrastCommand: public Command<IntegerValueMenuItem> {
  public:
    ChangeContrastCommand(Adafruit_PCD8544 &display): display(display) {
    }
    void run(IntegerValueMenuItem &item) {
        display.setContrast(item.getValue());
    }
  private:
    Adafruit_PCD8544 &display;
};

class ToggleBacklightCommand: public Command<BoolValueMenuItem> {
  public:
    ToggleBacklightCommand(int pin): pin(pin) {}
    void run(BoolValueMenuItem &item) {
        analogWrite(this->pin, item.getValue() ? 255 : 0);
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
    ReadLineCommand(QTRSensorsRC &qtr): qtr(qtr) {}
    void run(IntegerValueMenuItem &item) {
      unsigned int sensorValues[NUMBER_OF_REFLECTANT_SENSORS];
      item.setValue(this->qtr.readLine(sensorValues));
    }
  private:
    QTRSensorsRC &qtr;
};

class MotorCheckCommand: public Command<ActionMenuItem> {
  public:
    MotorCheckCommand(DRV8835MotorsDriver &motorsDriver, int motor, int speed): motorsDriver(motorsDriver), motor(motor), speed(speed) {}
    void run(ActionMenuItem &item) {
      if (this->motor == MOTOR_LEFT) {
        this->motorsDriver.setLeftMotorSpeed(this->speed);
      } else if (this->motor == MOTOR_RIGHT) {
        this->motorsDriver.setRightMotorSpeed(this->speed);
      }
      delay(2000);
      if (this->motor == MOTOR_LEFT) {
        this->motorsDriver.setLeftMotorSpeed(0);
      } else if (this->motor == MOTOR_RIGHT) {
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
    FollowCommand(Follower &follower, int stopButtonPin, unsigned long timeout): follower(follower), stopButtonPin(stopButtonPin), timeout(timeout) {}
    void run(ActionMenuItem &item) {
      unsigned long startTime = millis();
      while (digitalRead(this->stopButtonPin) == LOW || (millis() - startTime) > timeout) {
        this->follower.follow();
      }
    }
  private:
    Follower &follower;
    int stopButtonPin;
    unsigned long timeout;
};

#endif
