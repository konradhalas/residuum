#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "linedetector.h"
#include "motorsdriver.h"

class Follower {
  public:
    Follower(LineDetector &lineDetector, MotorsDriver &motorsDriver, float kP=0.1, float kD=5.0): lineDetector(lineDetector), motorsDriver(motorsDriver), kP(kP), kD(kD), lastError(0) {}
    void follow();
    void finish();
  private:
    LineDetector &lineDetector;
    MotorsDriver &motorsDriver;
    int lastError;
    float kP;
    float kD;
};

#endif
