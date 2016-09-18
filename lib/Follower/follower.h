#ifndef FOLLOWER_H
#define FOLLOWER_H

class MotorsDriver {
  public:
    int getLeftMotorBaseSpeed() { return 0; };
    int getRightMotorBaseSpeed() { return 0; };
};

class LineDetector {
  int detectLine();
  int getMaximumLineDetectionValue();
};

class Follower {
  public:
    Follower(LineDetector &lineDetector, MotorsDriver &motorsDriver) {}
    void follow() {};
};

#endif
