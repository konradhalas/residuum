#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "linedetector.h"
#include "motorsdriver.h"

class Follower {
  public:
    Follower(LineDetector &lineDetector, MotorsDriver &motorsDriver) {}
    void follow() {};
};

#endif
