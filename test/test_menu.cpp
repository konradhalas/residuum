#include <unity.h>

#ifdef UNIT_TEST

void test_test() {
  TEST_ASSERT_EQUAL(1, 1);
}

int main(int argc, char const *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_test);
  UNITY_END();
  return 0;
}

#endif
