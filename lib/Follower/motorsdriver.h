#ifndef MOTORS_DRIVER_H
#define MOTORS_DRIVER_H

class MotorsDriver {
  public:
    virtual void setLeftMotorSpeed(int speed) = 0;
    virtual void setRightMotorSpeed(int speed) = 0;
    virtual int getBaseMotorSpeed() = 0;
    virtual void setBaseMotorsSpeed(int speed) = 0;
};

#endif
