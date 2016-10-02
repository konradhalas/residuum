#ifndef UNIT_TEST

#include "qtrlinedetector.h"

QtrLineDetector::QtrLineDetector(QTRSensorsRC &qtr, int sensorsCount): qtr(qtr), sensorsCount(sensorsCount) {

}

int QtrLineDetector::detectLine() {
  unsigned int sensorValues[this->sensorsCount];
  return this->qtr.readLine(sensorValues) - (sensorsCount * 1000 / 2);
}

#endif
