#include "follower.h"

void Follower::follow() {
  int error = this->lineDetector.detectLine();
  int speedDelta = this->kP * error + this->kD * (error - this->lastError);
  this->lastError = error;
  this->motorsDriver.setLeftMotorSpeed(this->motorsDriver.getBaseMotorSpeed() + speedDelta);
  this->motorsDriver.setRightMotorSpeed(this->motorsDriver.getBaseMotorSpeed() - speedDelta);
}

void Follower::finish() {
  this->motorsDriver.setLeftMotorSpeed(0);
  this->motorsDriver.setRightMotorSpeed(0);
}
