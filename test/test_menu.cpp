#include <unity.h>
#include "menu.h"

#ifdef UNIT_TEST

class TestMenuRenderer: public MenuRenderer {
  public:
    TestMenuRenderer() {
      this->renderedProgress = false;
    }
    void renderItem(const IntegerValueMenuItem &item, bool isSelected) {
      this->renderItem(isSelected);
    };
    void renderItem(const BoolValueMenuItem &item, bool isSelected) {
      this->renderItem(isSelected);
    };
    void renderItem(const ActionMenuItem &item, bool isSelected){
      this->renderItem(isSelected);
    };
    void renderItem(const SubMenuItem &item, bool isSelected){
      this->renderItem(isSelected);
    };
    void renderItem(const ParentMenuItem &item, bool isSelected){
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
    void renderProgress(const MenuItem &item) {
      this->renderedProgress = true;
    }
    int getItemsLimit() { return 5; };
    int renderedItemsCount;
    int selectedNodeNumber;
    bool isEditMode;
    bool renderedProgress;
};

class TestMenuActionsProvider: public MenuActionsProvider {
  public:
    TestMenuActionsProvider(bool toggleEditModeAction = false, bool nextAction = false, bool previousAction = false) {
      this->toggleEditModeAction = toggleEditModeAction;
      this->nextAction = nextAction;
      this->previousAction = previousAction;
    }
    bool isToggleEditModeAction() {
      return toggleEditModeAction;
    };
    bool isNextAction() {
      return nextAction;
    };
    bool isPreviousAction() {
      return previousAction;
    };
    void afterActionHandler() {
    };
    bool toggleEditModeAction;
    bool nextAction;
    bool previousAction;
};

template <typename T>
class TestCommand: public Command<T> {
  public:
    TestCommand(): isAfterRun(false) {};
    void run(T &item) {
      isAfterRun = true;
    }
    bool isAfterRun;
};

template <typename T, typename V>
class TestUpdateCommand: public Command<T> {
  public:
    TestUpdateCommand(V value): value(value) {};
    void run(T &item) {
      item.setValue(this->value);
    }
    V value;
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

void test_handle_with_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider();
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(new IntegerValueMenuItem("item", 1));

  menu.handle();

  TEST_ASSERT_EQUAL(1, renderer.renderedItemsCount);
  TEST_ASSERT_EQUAL(0, renderer.selectedNodeNumber);
}

void test_handle_with_more_items_above_limit() {
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

void test_handle_previous_action_with_single_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, false, true);
  Menu menu = Menu(renderer, actionsProvider);
  menu.addItem(new IntegerValueMenuItem("item1", 1));

  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
}

void test_handle_previous_action_with_many_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, false, true);
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
  IntegerValueMenuItem *item = new IntegerValueMenuItem("item1", 1, new TestCommand<IntegerValueMenuItem>());
  menu.addItem(item);
  menu.addItem(new IntegerValueMenuItem("item2", 1, new TestCommand<IntegerValueMenuItem>()));

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
  menu.addItem(new IntegerValueMenuItem("item", 1, new TestCommand<IntegerValueMenuItem>()));

  menu.handle();

  TEST_ASSERT_EQUAL(renderer.selectedNodeNumber, 0);
  TEST_ASSERT_TRUE(renderer.isEditMode);
}

void test_handle_toggle_edit_mode_action_with_non_editable_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(true, false);
  Menu menu = Menu(renderer, actionsProvider);
  TestCommand<ActionMenuItem> *command = new TestCommand<ActionMenuItem>();
  menu.addItem(new ActionMenuItem("item", command));

  menu.handle();

  TEST_ASSERT_FALSE(renderer.isEditMode);
  TEST_ASSERT_TRUE(renderer.renderedProgress);
  TEST_ASSERT_TRUE(command->isAfterRun);
}

void test_integer_value_menu_item_handle_next_action() {
  TestCommand<IntegerValueMenuItem> *command = new TestCommand<IntegerValueMenuItem>();
  IntegerValueMenuItem item = IntegerValueMenuItem("item", 1, command);

  item.handleNextAction();

  TEST_ASSERT_EQUAL(2, item.getValue());
  TEST_ASSERT_TRUE(command->isAfterRun);
}

void test_bool_value_menu_item_handle_next_action() {
  TestCommand<BoolValueMenuItem> *command = new TestCommand<BoolValueMenuItem>();
  BoolValueMenuItem item = BoolValueMenuItem("item", false, command);

  item.handleNextAction();

  TEST_ASSERT_TRUE(item.getValue());
  TEST_ASSERT_TRUE(command->isAfterRun);
}

void test_handle_value_menu_item_auto_update() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(false, false);
  Menu menu = Menu(renderer, actionsProvider);
  TestUpdateCommand<IntegerValueMenuItem, int> *command = new TestUpdateCommand<IntegerValueMenuItem, int>(2);
  IntegerValueMenuItem *item = new IntegerValueMenuItem("item", 1, NULL, command);
  menu.addItem(item);

  menu.handle();

  TEST_ASSERT_EQUAL(2, item->getValue());
}

void test_handle_toggle_edit_mode_action_with_submenu_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(true, false);
  Menu menu = Menu(renderer, actionsProvider);
  TestCommand<ActionMenuItem> *command = new TestCommand<ActionMenuItem>();
  SubMenuItem *subMenuItem = new SubMenuItem("item", &menu);
  subMenuItem->addItem(new ActionMenuItem("item1", NULL));
  subMenuItem->addItem(new ActionMenuItem("item2", NULL));
  subMenuItem->addItem(new ActionMenuItem("item3", NULL));
  menu.addItem(subMenuItem);

  menu.handle();

  TEST_ASSERT_EQUAL(4, renderer.renderedItemsCount);
}

void test_handle_toggle_edit_mode_action_with_parent_menu_item() {
  TestMenuRenderer renderer = TestMenuRenderer();
  TestMenuActionsProvider actionsProvider = TestMenuActionsProvider(true, false);
  Menu menu = Menu(renderer, actionsProvider);
  TestCommand<ActionMenuItem> *command = new TestCommand<ActionMenuItem>();
  SubMenuItem *subMenuItem = new SubMenuItem("item", &menu);
  subMenuItem->addItem(new ActionMenuItem("item1", NULL));
  subMenuItem->addItem(new ActionMenuItem("item2", NULL));
  subMenuItem->addItem(new ActionMenuItem("item3", NULL));
  menu.addItem(subMenuItem);

  menu.handle();
  menu.handle();

  TEST_ASSERT_EQUAL(1, renderer.renderedItemsCount);
}

#endif
