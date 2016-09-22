#ifndef COMMANDS_H
#define COMMANDS_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <QTRSensors.h>

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
      item.setValue(sensorValues[this->qtr.readLine(sensorValues)]);
    }
  private:
    QTRSensorsRC &qtr;
};

#endif
