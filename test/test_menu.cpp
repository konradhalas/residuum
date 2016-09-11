#include <unity.h>
#include "menu.h"

#ifdef UNIT_TEST

class TestMenuRenderer: public MenuRenderer {
  public:
    void renderItem(const IntegerValueMenuItem &item, bool isSelected) {
      this->renderItem(isSelected);
    };
    void renderItem(const ActionMenuItem &item, bool isSelected){
      this->renderItem(isSelected);
    };
    void renderItem(bool isSelected) {
      if (isSelected) {
        this->selectedNodeNumber = this->renderedItemsCount;
      }
      ++this->renderedItemsCount;
    };
    void renderStart(bool isEditMode) {
      this->renderedItemsCount = 0;
      this->selectedNodeNumber = -1;
      this->isEditMode = isEditMode;
    };
    void renderFinish() {};
    int getItemsLimit() { return 5; };
    int renderedItemsCount;
    int selectedNodeNumber;
    bool isEditMode;
};

class TestMenuActionsProvider: public MenuActionsProvider {
  public:
    TestMenuActionsProvider(bool toggleEditModeAction = false, bool nextAction = false) {
      this->toggleEditModeAction = toggleEditModeAction;
      this->nextAction = nextAction;
    }
    bool isToggleEditModeAction() {
      return toggleEditModeAction;
    };
    bool isNextAction() {
      return nextAction;
    };
    void afterActionHandler() {
    };
    bool toggleEditModeAction;
    bool nextAction;
};

class TestCommand: public Command<ActionMenuItem> {
  public:
    TestCommand(): isAfterRun(false) {};
    void run(const ActionMenuItem &item) {
      isAfterRun = true;
    }
    bool isAfterRun;
};

void test_add_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider();
  Menu menu = Menu(renderer, actionsProvider);

  menu.addItem(new IntegerValueMenuItem("item", 1));

  TEST_ASSERT_EQUAL(menu.getItemsCount(), 1);
  TEST_ASSERT_TRUE(menu.getItem(0)->getName() == "item");
}

void test_add_many_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider();
  Menu menu = Menu(renderer, actionsProvider);

  menu.addItem(new IntegerValueMenuItem("item1", 1));
  menu.addItem(new IntegerValueMenuItem("item2", 2));

  TEST_ASSERT_EQUAL(menu.getItemsCount(), 2);
  TEST_ASSERT_TRUE(menu.getItem(0)->getName() == "item1");
  TEST_ASSERT_TRUE(menu.getItem(1)->getName() == "item2");
}

void test_render_with_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider();
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(new IntegerValueMenuItem("item", 1));

  menu.render();

  TEST_ASSERT_EQUAL(renderer.renderedItemsCount, 1);
  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
}

void test_render_with_more_items_above_limit() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, true);
  Menu menu = Menu(renderer, actionsProvider);
  for (int i = 0; i < 10; ++i) {
    menu.addItem(new IntegerValueMenuItem("item", 1));
  }

  for (int i = 0; i < 9; ++i) {
    menu.handle();
  }

  TEST_ASSERT_EQUAL(5, renderer.renderedItemsCount);
  TEST_ASSERT_EQUAL(4, renderer.selectedNodeNumber);
}

void test_handle_next_action_with_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, true);
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(new IntegerValueMenuItem("item1", 1));

  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
}

void test_handle_next_action_with_many_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, true);
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(new IntegerValueMenuItem("item1", 1));
  menu.addItem(new IntegerValueMenuItem("item2", 1));

  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 1);
}

void test_handle_next_action_when_edit_mode() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(true, false);
  Menu menu = Menu(renderer, actionsProvider);
  IntegerValueMenuItem *item = new IntegerValueMenuItem("item1", 1);
  menu.addItem(item);
  menu.addItem(new IntegerValueMenuItem("item2", 1));

  menu.handle();
  actionsProvider.toggleEditModeAction = false;
  actionsProvider.nextAction = true;
  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
  TEST_ASSERT_EQUAL(item->getValue(), 2);
}

void test_handle_toggle_edit_mode_action_with_editable_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(true, false);
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(new IntegerValueMenuItem("item", 1));

  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
  TEST_ASSERT_TRUE(renderer.isEditMode);
}

void test_handle_toggle_edit_mode_action_with_non_editable_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(true, false);
  Menu menu = Menu(renderer, actionsProvider);
  TestCommand *command = new TestCommand();
  menu.addItem(new ActionMenuItem("item", command));

  menu.handle();

  TEST_ASSERT_FALSE(renderer.isEditMode);
  TEST_ASSERT_TRUE(command->isAfterRun);
}

int main(int argc, char const *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_add_single_item);
  RUN_TEST(test_add_many_item);
  RUN_TEST(test_render_with_single_item);
  RUN_TEST(test_render_with_more_items_above_limit);
  RUN_TEST(test_handle_next_action_with_single_item);
  RUN_TEST(test_handle_next_action_with_many_item);
  RUN_TEST(test_handle_toggle_edit_mode_action_with_editable_item);
  RUN_TEST(test_handle_toggle_edit_mode_action_with_non_editable_item);
  RUN_TEST(test_handle_next_action_when_edit_mode);
  UNITY_END();
  return 0;
}

#endif
