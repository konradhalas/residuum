#include "follower.h"

void Follower::follow() {
  int error = this->lineDetector.detectLine();
  int speedDelta = this->kP * error + this->kD * (error - this->lastError);
  this->lastError = error;
  this->motorsDriver.setLeftMotorSpeed(this->baseMotorsSpeed + speedDelta);
  this->motorsDriver.setRightMotorSpeed(this->baseMotorsSpeed - speedDelta);
}
