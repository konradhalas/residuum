#include <unity.h>
#include "follower.h"

#ifdef UNIT_TEST

class TestMotorsDriver: public MotorsDriver {
  public:
    void setLeftMotorSpeed(int speed) {
      this->leftMotorSpeed = speed;
    }
    void setRightMotorSpeed(int speed) {
      this->rightMotorSpeed = speed;
    }
    int getBaseMotorSpeed() {
      return 10;
    }
    void setBaseMotorsSpeed(int speed) {}
    int leftMotorSpeed;
    int rightMotorSpeed;
};

class TestLineDetector: public LineDetector {
  public:
    TestLineDetector(int line): line(line){}
    int detectLine() {
      return this->line;
    }
    int line;
};

void test_follow_go_straight() {
  TestMotorsDriver motorsDriver = TestMotorsDriver();
  TestLineDetector lineDetector = TestLineDetector(0);
  Follower follower = Follower(lineDetector, motorsDriver);

  follower.follow();

  TEST_ASSERT_TRUE(motorsDriver.leftMotorSpeed > 0);
  TEST_ASSERT_TRUE(motorsDriver.rightMotorSpeed > 0);
  TEST_ASSERT_EQUAL(motorsDriver.leftMotorSpeed, motorsDriver.rightMotorSpeed);
}

void test_follow_turn_left() {
  TestMotorsDriver motorsDriver = TestMotorsDriver();
  TestLineDetector lineDetector = TestLineDetector(-1000);
  Follower follower = Follower(lineDetector, motorsDriver);

  follower.follow();

  TEST_ASSERT_TRUE(motorsDriver.leftMotorSpeed < motorsDriver.rightMotorSpeed);
}

void test_follow_turn_right() {
  TestMotorsDriver motorsDriver = TestMotorsDriver();
  TestLineDetector lineDetector = TestLineDetector(1000);
  Follower follower = Follower(lineDetector, motorsDriver);

  follower.follow();

  TEST_ASSERT_TRUE(motorsDriver.leftMotorSpeed > motorsDriver.rightMotorSpeed);
}

void test_follow_turn_faster() {
  TestMotorsDriver firstMotorsDriver = TestMotorsDriver();
  TestLineDetector firstLineDetector = TestLineDetector(-1000);
  Follower firstFollower = Follower(firstLineDetector, firstMotorsDriver);
  TestMotorsDriver secondMotorsDriver = TestMotorsDriver();
  TestLineDetector secondLineDetector = TestLineDetector(1000);
  Follower secondFollower = Follower(secondLineDetector, secondMotorsDriver);

  firstFollower.follow();
  secondFollower.follow();

  TEST_ASSERT_TRUE(firstMotorsDriver.rightMotorSpeed > secondMotorsDriver.rightMotorSpeed);
  TEST_ASSERT_TRUE(firstMotorsDriver.leftMotorSpeed < secondMotorsDriver.leftMotorSpeed);
}

#endif
