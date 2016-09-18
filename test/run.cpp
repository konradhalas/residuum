#include <unity.h>
#include "tests.h"

#ifdef UNIT_TEST

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
  RUN_TEST(test_integer_value_menu_item_handle_next_action);
  RUN_TEST(test_bool_value_menu_item_handle_next_action);
  RUN_TEST(test_handle_value_menu_item_auto_update);

  RUN_TEST(test_follow_straight);

  UNITY_END();
  return 0;
}

#endif
