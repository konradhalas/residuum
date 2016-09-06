#include <Arduino.h>
#include <Menu.hpp>

#define BUTTONS_DELAY 500

MenuNode::MenuNode(MenuItem *item) {
  this->item = item;
}

MenuItem* MenuNode::getItem() {
  return item;
}

boolean MenuNode::hasNext() {
  return next != NULL;
}

MenuNode* MenuNode::getNext() {
  return next;
}

boolean MenuNode::hasPrevious() {
  return previous != NULL;
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

MenuItem::MenuItem(String name, int value) {
  this->name = name;
  this->value = value;
}

String MenuItem::getName() {
  return name;
}

int MenuItem::getValue() {
  return value;
}

void MenuItem::setValue(int value) {
  this->value = value;
}

Menu::Menu(Adafruit_PCD8544 & display, int selectButtonPin, int nextButtonPin) : display(display) {
  this->selectButtonPin = selectButtonPin;
  this->nextButtonPin = nextButtonPin;
  pinMode(selectButtonPin, INPUT);
  pinMode(nextButtonPin, INPUT);
}

void Menu::addItem(String itemName, int value) {
  itemName.remove(5);

  MenuItem *item = new MenuItem(itemName, value);

  if (root == NULL) {
    root = new MenuNode(item);
    root->setNext(root);
    root->setPrevious(root);
    currentNode = root;
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
  this->display.clearDisplay();
  this->display.setTextSize(1);
  this->display.setTextColor(BLACK);
  this->display.setCursor(0, 0);
  MenuNode *current = root;
  if (current) {
    do {
      String prefix;
      if (current == currentNode) {
        if (isItemSelected) {
          prefix = "#";
        } else {
          prefix = ">";
        }
      } else {
        prefix = " ";
      }
      this->display.println(prefix + current->getItem()->getName() + " = " + current->getItem()->getValue());
      current = current->getNext();
    } while (current != root);
  }
  this->display.display();
}

void Menu::nextItem() {
  this->currentNode = this->currentNode->getNext();
}

void Menu::previousItem() {
  this->currentNode = this->currentNode->getPrevious();
}

void Menu::toggleSelectItem() {
  isItemSelected = !isItemSelected;
}

void Menu::incrementSelectedItem() {
  currentNode->getItem()->setValue(currentNode->getItem()->getValue() + 1);
}

void Menu::handle() {
  int selectButtonState = digitalRead(selectButtonPin);
  int nextButtonState = digitalRead(nextButtonPin);
  if (selectButtonState == HIGH) {
    if (isItemSelected) {
      incrementSelectedItem();
    } else {
      nextItem();
    }
    render();
    delay(BUTTONS_DELAY);
  }

  if (nextButtonState == HIGH) {
    toggleSelectItem();
    render();
    delay(BUTTONS_DELAY);
  }
}
