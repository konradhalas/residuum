#include "follower.h"

void Follower::follow() {
  // TODO: implement PID
  if (this->lineDetector.detectLine() < (this->lineDetector.getLineMax() / 2 ) ) {
    this->motorsDriver.setRightMotorSpeed(40);
    this->motorsDriver.setLeftMotorSpeed(10);
  } else if (this->lineDetector.detectLine() > (this->lineDetector.getLineMax() / 2 ) ) {
    this->motorsDriver.setRightMotorSpeed(10);
    this->motorsDriver.setLeftMotorSpeed(40);
  } else {
    this->motorsDriver.setLeftMotorSpeed(10);
    this->motorsDriver.setRightMotorSpeed(10);
  }
}
