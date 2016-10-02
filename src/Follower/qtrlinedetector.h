#ifndef QTR_LINE_DETECTOR_H
#define QTR_LINE_DETECTOR_H

#include <QTRSensors.h>

#include <follower.h>

class QtrLineDetector: public LineDetector {
  public:
    QtrLineDetector(QTRSensorsRC &qtr, int sensorsCount);
    int detectLine();
  private:
    QTRSensorsRC &qtr;
    int sensorsCount;
};

#endif
