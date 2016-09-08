#include <unity.h>
#include "menu.h"

#ifdef UNIT_TEST

class TestMenuRenderer: public MenuRenderer {
  public:
    void render(Menu &menu) {
    }
};

class TestMenuActionsProvider: public MenuActionsProvider {
  public:
    bool isSelectAction() {
      return false;
    };
    bool isNextAction() {
      return false;
    };
    void afterActionHandler() {
    };
};

void test_add_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider();
  Menu menu = Menu(renderer, actionsProvider);

  menu.addItem(MenuItem("item", 1));

  TEST_ASSERT_EQUAL(menu.getItemsCount(), 1);
  TEST_ASSERT_TRUE(menu.getItem(0).getName() == "item");
}

void test_add_many_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider();
  Menu menu = Menu(renderer, actionsProvider);

  menu.addItem(MenuItem("item1", 1));
  menu.addItem(MenuItem("item2", 2));

  TEST_ASSERT_EQUAL(menu.getItemsCount(), 2);
  TEST_ASSERT_TRUE(menu.getItem(0).getName() == "item1");
  TEST_ASSERT_TRUE(menu.getItem(1).getName() == "item2");
}

int main(int argc, char const *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_add_single_item);
  RUN_TEST(test_add_many_item);
  UNITY_END();
  return 0;
}

#endif
