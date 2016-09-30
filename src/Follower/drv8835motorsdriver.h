#ifndef ARDUINO_FOLLOWR_H
#define ARDUINO_FOLLOWR_H

#include <follower.h>

class DRV8835MotorsDriver: public MotorsDriver {
  public:
    DRV8835MotorsDriver(int leftMotorPhasePin, int leftMotorEnablePin, int rightMotorPhasePin, int rightMotorEnablePin);
    void setup();
    void setLeftMotorSpeed(int speed);
    void setRightMotorSpeed(int speed);
  private:
    void setSpeed(int phasePin, int enablePin, int speed);
    int leftMotorPhasePin;
    int leftMotorEnablePin;
    int rightMotorPhasePin;
    int rightMotorEnablePin;
};

#endif
