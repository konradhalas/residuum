#include <unity.h>
#include "follower.h"

#ifdef UNIT_TEST

class TestMotorsDriver: public MotorsDriver {
  public:
    int leftMotorSpeed;
    int rightMotorSpeed;
};

class TestLineDetector: public LineDetector {

};

void test_follow_straight() {
  TestMotorsDriver motorsDriver = TestMotorsDriver();
  TestLineDetector lineDetector = TestLineDetector();
  Follower follower = Follower(lineDetector, motorsDriver);

  follower.follow();

  TEST_ASSERT_EQUAL(motorsDriver.getLeftMotorBaseSpeed(), motorsDriver.leftMotorSpeed);
  TEST_ASSERT_EQUAL(motorsDriver.getRightMotorBaseSpeed(), motorsDriver.rightMotorSpeed);
}

#endif
