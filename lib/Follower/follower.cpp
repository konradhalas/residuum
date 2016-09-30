#include "follower.h"

void Follower::follow() {
  // TODO: implement PID
  this->motorsDriver.setLeftMotorSpeed(10);
  this->motorsDriver.setRightMotorSpeed(10);
}
