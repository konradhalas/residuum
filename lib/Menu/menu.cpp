#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
typedef std::string String;
#endif

#include <menu.h>

MenuNode::MenuNode(MenuItem* item): item(item) {
  this->previous = NULL;
  this->next = NULL;
}

MenuNode::~MenuNode() {
  delete this->item;
}

MenuItem* MenuNode::getItem() {
  return item;
}

MenuNode* MenuNode::getNext() {
  return next;
}

MenuNode* MenuNode::getPrevious() {
  return previous;
}

void MenuNode::setNext(MenuNode *node) {
  this->next = node;
}

void MenuNode::setPrevious(MenuNode *node) {
  this->previous = node;
}

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

Menu::Menu(MenuRenderer & renderer, MenuActionsProvider & actionsProvider) : renderer(renderer), actionsProvider(actionsProvider) {
  this->selectedNode = NULL;
  this->root = NULL;
  this->isEditMode = false;
}

void Menu::addItem(MenuItem *item) {
  if (root == NULL) {
    root = new MenuNode(item);
    root->setNext(root);
    root->setPrevious(root);
    selectedNode = root;
  } else {
    MenuNode *last = root;
    while (last->getNext() != root) {
      last = last->getNext();
    }
    MenuNode *node = new MenuNode(item);
    last->setNext(node);
    node->setPrevious(last);
    node->setNext(root);
    root->setPrevious(node);
  }
}

void Menu::render() {
  this->renderer.renderStart(this->isEditMode);
  MenuNode *current = root;

  int currentItemIndex = -1;
  int selectedItemIndex = this->getSelectedItemIndex();

  int startItemIndex, endItemIndex;
  if (this->renderer.getItemsLimit() == 0) {
    startItemIndex = 0;
    endItemIndex = this->getItemsCount() - 1;
  } else {
    startItemIndex = (selectedItemIndex / this->renderer.getItemsLimit()) * this->renderer.getItemsLimit();
    endItemIndex = startItemIndex + this->renderer.getItemsLimit() - 1;
  }

  do {
    ++currentItemIndex;
    if (startItemIndex <= currentItemIndex && endItemIndex >= currentItemIndex) {
      MenuItem *item = current->getItem();
      item->renderDispatch(this->renderer, current == selectedNode);
    }
    current = current->getNext();
  } while (current != root);
  this->renderer.renderFinish();
}

int Menu::getSelectedItemIndex() const {
  if (root == NULL) {
    return -1;
  }
  int selectedItemIndex = 0;
  MenuNode *current = root;
  while (current != this->selectedNode) {
    current = current->getNext();
    ++selectedItemIndex;
  }
  return selectedItemIndex;
}

MenuItem* Menu::getItem(int i) const {
  int count = 0;
  MenuNode *current = root;
  while (current->getNext() != root && count < i) {
    ++count;
    current = current->getNext();
  }
  return current->getItem();
}

int Menu::getItemsCount() const {
  int count = 0;
  if (root != NULL) {
    MenuNode *current = root;
    do {
      ++count;
      current = current->getNext();
    } while(current != root);
  }
  return count;
}

void Menu::handle() {
  bool handledAction = false;

  if (root != NULL) {
    MenuNode *current = root;
    do {
      bool handled = current->getItem()->handleTick();
      if (handled) {
        handledAction = true;
      }
      current = current->getNext();
    } while (current != root);
  }

  if (this->actionsProvider.isToggleEditModeAction()) {
    if (this->isEditMode){
      this->isEditMode = false;
    } else {
      bool isEditable = this->selectedNode->getItem()->handleEditAction();
      this->isEditMode = isEditable;
    }
    handledAction = true;
  } else if (this->actionsProvider.isNextAction()) {
    if (this->isEditMode) {
      this->selectedNode->getItem()->handleNextAction();
    } else {
      this->selectedNode = this->selectedNode->getNext();
    }
    handledAction = true;
  } else if (this->actionsProvider.isPreviousAction()) {
    if (this->isEditMode) {
      this->selectedNode->getItem()->handlePreviousAction();
    } else {
      this->selectedNode = this->selectedNode->getPrevious();
    }
    handledAction = true;
  }

  if (handledAction) {
    render();
    this->actionsProvider.afterActionHandler();
  }
}

Menu::~Menu() {
  if (root == NULL) {
    return;
  }
  MenuNode *current = root;
  MenuNode *next = NULL;
  do {
    next = current->getNext();
    delete current;
    current = next;
  } while (current != root);
}
