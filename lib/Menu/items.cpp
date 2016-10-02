#include "items.h"

IntegerValueMenuItem::IntegerValueMenuItem(String name, int value, Command<IntegerValueMenuItem> *onValueChangeCommand, Command<IntegerValueMenuItem> *valueUpdateCommand) : ValueMenuItem<int, Command<IntegerValueMenuItem> >(name, value, onValueChangeCommand, valueUpdateCommand) {}

void IntegerValueMenuItem::updateValueOnNextAction() {
  this->setValue(this->getValue() + 1);
}

void IntegerValueMenuItem::updateValueOnPreviousAction() {
  this->setValue(this->getValue() - 1);
}

void IntegerValueMenuItem::renderDispatch(MenuRenderer &renderer, bool isSelected) {
  renderer.renderItem(*this, isSelected);
}

void IntegerValueMenuItem::dispatchCommandRun(Command<IntegerValueMenuItem> *command) {
  command->run(*this);
};

BoolValueMenuItem::BoolValueMenuItem(String name, bool value, Command<BoolValueMenuItem> *onValueChangeCommand, Command<BoolValueMenuItem> *valueUpdateCommand) : ValueMenuItem<bool, Command<BoolValueMenuItem> >(name, value, onValueChangeCommand, valueUpdateCommand) {}

void BoolValueMenuItem::updateValueOnNextAction() {
  this->setValue(!this->getValue());
}

void BoolValueMenuItem::updateValueOnPreviousAction() {
  this->setValue(!this->getValue());
}

void BoolValueMenuItem::renderDispatch(MenuRenderer &renderer, bool isSelected) {
  renderer.renderItem(*this, isSelected);
}

void BoolValueMenuItem::dispatchCommandRun(Command<BoolValueMenuItem> *command) {
  command->run(*this);
};

ActionMenuItem::ActionMenuItem(String name, Command<ActionMenuItem> *command) : MenuItem(name) {
  this->command = command;
}

void ActionMenuItem::renderDispatch(MenuRenderer &renderer, bool isSelected) {
  renderer.renderItem(*this, isSelected);
}

void ActionMenuItem::handleNextAction() {
}

void ActionMenuItem::handlePreviousAction() {
}

bool ActionMenuItem::handleEditAction() {
  if (command != NULL) {
    command->run(*this);
  }
  return false;
}

bool ActionMenuItem::shouldShowProgress() {
  return true;
}
