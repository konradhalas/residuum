#include <unity.h>
#include "menu.h"

#ifdef UNIT_TEST

class TestMenuRenderer: public MenuRenderer {
  public:
    void renderItem(const MenuItem &item, bool isSelected) {
        if (isSelected) {
          selectedNodeNumber = renderedItemsCount;
        }
        ++renderedItemsCount;
    };
    void renderStart() {
      renderedItemsCount = 0;
      selectedNodeNumber = -1;
    };
    void renderFinish() {};
    int renderedItemsCount;
    int selectedNodeNumber;
};

class TestMenuActionsProvider: public MenuActionsProvider {
  public:
    TestMenuActionsProvider(bool selectAction = false, bool nextAction = false) {
      this->selectAction = selectAction;
      this->nextAction = nextAction;
    }
    bool isToggleModeAction() {
      return selectAction;
    };
    bool isNextAction() {
      return nextAction;
    };
    void afterActionHandler() {
    };
    bool selectAction;
    bool nextAction;
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

void test_render_with_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider();
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(MenuItem("item", 1));

  menu.render();

  TEST_ASSERT_EQUAL(renderer.renderedItemsCount, 1);
  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
}

void test_handle_next_action_with_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, true);
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(MenuItem("item1", 1));

  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
}

void test_handle_next_action_with_many_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, true);
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(MenuItem("item1", 1));
  menu.addItem(MenuItem("item2", 1));

  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 1);
}

int main(int argc, char const *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_add_single_item);
  RUN_TEST(test_add_many_item);
  RUN_TEST(test_render_with_single_item);
  RUN_TEST(test_handle_next_action_with_many_item);
  UNITY_END();
  return 0;
}

#endif
