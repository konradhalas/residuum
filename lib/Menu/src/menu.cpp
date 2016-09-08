#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
typedef std::string String;
#endif

#include <menu.h>

MenuNode::MenuNode(const MenuItem item): item(item) {
  this->previous = NULL;
  this->next = NULL;
}

MenuItem & MenuNode::getItem() {
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

MenuItem::MenuItem(const MenuItem &item) {
    this->name = item.name;
    this->value = item.value;
}

MenuItem::MenuItem(String name, int value) {
  this->name = name;
  this->value = value;
}

String MenuItem::getName() const {
  return name;
}

int MenuItem::getValue() const {
  return value;
}

void MenuItem::setValue(int value) {
  this->value = value;
}

Menu::Menu(MenuRenderer & renderer, MenuActionsProvider & actionsProvider) : renderer(renderer), actionsProvider(actionsProvider) {
  this->selectedNode = NULL;
  this->root = NULL;
  this->isItemSelected = false;
}

void Menu::addItem(const MenuItem item) {
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
  this->renderer.renderStart();
  MenuNode *current = root;
  do {
    MenuItem &item = current->getItem();
    this->renderer.renderItem(item, current == selectedNode);
    current = current->getNext();
  } while (current != root);
  this->renderer.renderFinish();
}

MenuItem& Menu::getItem(int i) const {
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
  if (this->actionsProvider.isToggleModeAction()) {
    if (isItemSelected) {
      // currentNode->getItem().setValue(currentNode->getItem().getValue() + 1);
    } else {
      this->selectedNode = this->selectedNode->getNext();
    }
    handledAction = true;
  }

  if (this->actionsProvider.isNextAction()) {
    this->selectedNode = this->selectedNode->getNext();
    handledAction = true;
  }
  if (handledAction) {
    render();
    this->actionsProvider.afterActionHandler();
  }
}
