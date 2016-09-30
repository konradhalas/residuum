#include <unity.h>
#include "follower.h"

#ifdef UNIT_TEST

class TestMotorsDriver: public MotorsDriver {
  public:
    void setLeftMotorSpeed(int speed) {
      this->leftMotorSpeed = speed;
    }
    virtual void setRightMotorSpeed(int speed) {
      this->rightMotorSpeed = speed;
    }
    int leftMotorSpeed;
    int rightMotorSpeed;
};

class TestLineDetector: public LineDetector {
  public:
    TestLineDetector(int line, int max): line(line), max(max) {}
    int detectLine() {
      return this->line;
    }
    int getLineMax() {
      return this->max;
    }
    int line;
    int max;
};

void test_follow_straight() {
  TestMotorsDriver motorsDriver = TestMotorsDriver();
  TestLineDetector lineDetector = TestLineDetector(4000, 8000);
  Follower follower = Follower(lineDetector, motorsDriver);

  follower.follow();

  TEST_ASSERT_TRUE(motorsDriver.leftMotorSpeed > 0);
  TEST_ASSERT_TRUE(motorsDriver.rightMotorSpeed > 0);
  TEST_ASSERT_EQUAL(motorsDriver.leftMotorSpeed, motorsDriver.rightMotorSpeed);
}

#endif
