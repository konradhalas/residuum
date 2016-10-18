#ifndef DRV8835_MOTORS_DRIVER_H
#define DRV8835_MOTORS_DRIVER_H

#include <follower.h>

class DRV8835MotorsDriver: public MotorsDriver {
  public:
    DRV8835MotorsDriver(int leftMotorPhasePin, int leftMotorEnablePin, int rightMotorPhasePin, int rightMotorEnablePin, int baseSpeed);
    void setup();
    void setLeftMotorSpeed(int speed);
    void setRightMotorSpeed(int speed);
    int getBaseMotorSpeed();
    void setBaseMotorsSpeed(int speed);
  private:
    void setSpeed(int phasePin, int enablePin, int speed);
    int leftMotorPhasePin;
    int leftMotorEnablePin;
    int rightMotorPhasePin;
    int rightMotorEnablePin;
    int baseSpeed;
};

#endif
