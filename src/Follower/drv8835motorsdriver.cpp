#ifndef UNIT_TEST

#include <Arduino.h>

#include "drv8835motorsdriver.h"

DRV8835MotorsDriver::DRV8835MotorsDriver(int leftMotorPhasePin, int leftMotorEnablePin, int rightMotorPhasePin, int rightMotorEnablePin): leftMotorPhasePin(leftMotorPhasePin), leftMotorEnablePin(leftMotorEnablePin), rightMotorPhasePin(rightMotorPhasePin), rightMotorEnablePin(rightMotorEnablePin) {

}

void DRV8835MotorsDriver::setup() {
  pinMode(this->leftMotorEnablePin, OUTPUT);
  pinMode(this->leftMotorPhasePin, OUTPUT);
  digitalWrite(this->leftMotorEnablePin, LOW);
  digitalWrite(this->leftMotorPhasePin, LOW);
  pinMode(this->rightMotorEnablePin, OUTPUT);
  pinMode(this->rightMotorPhasePin, OUTPUT);
  digitalWrite(this->rightMotorEnablePin, LOW);
  digitalWrite(this->rightMotorPhasePin, LOW);
}

void DRV8835MotorsDriver::setLeftMotorSpeed(int speed) {
  this->setSpeed(this->leftMotorPhasePin, this->leftMotorEnablePin, speed);
}

void DRV8835MotorsDriver::setRightMotorSpeed(int speed) {
  this->setSpeed(this->rightMotorPhasePin, this->rightMotorEnablePin, speed);
}

void DRV8835MotorsDriver::setSpeed(int phasePin, int enablePin, int speed) {
  digitalWrite(phasePin, speed > 0 ? HIGH : LOW);
  if (speed < 0) {
    speed = - speed;
  }
  analogWrite(enablePin, speed);
}

#endif
