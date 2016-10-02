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

Menu::Menu(MenuRenderer & renderer, MenuActionsProvider & actionsProvider, int handleTickFrequency) : MenuItemsContainer(), renderer(renderer), actionsProvider(actionsProvider), handleTickFrequency(handleTickFrequency) {
  this->selectedMenuItem = NULL;
  this->isEditMode = false;
  this->tickNumber = 0;
  this->rendered = false;
}

MenuItemsContainer::MenuItemsContainer() {
  this->root = NULL;
}

void MenuItemsContainer::addItem(MenuItem *item) {
  if (root == NULL) {
    root = new MenuNode(item);
    root->setNext(root);
    root->setPrevious(root);
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

  int selectedItemIndex = this->getSelectedItemIndex();
  int itemsCount = this->getItemsCount();

  int startItemIndex, endItemIndex;
  if (this->renderer.getItemsLimit() == 0) {
    startItemIndex = 0;
    endItemIndex = itemsCount - 1;
  } else {
    startItemIndex = (selectedItemIndex / this->renderer.getItemsLimit()) * this->renderer.getItemsLimit();
    endItemIndex = startItemIndex + this->renderer.getItemsLimit() - 1;
  }
  for (int i = startItemIndex; i <= endItemIndex && i < itemsCount; i++) {
    this->getItem(i)->renderDispatch(this->renderer, selectedItemIndex == i);
  }
  this->renderer.renderFinish();
}

int Menu::getSelectedItemIndex() const {
  if (!this->getItemsCount()) {
    return -1;
  }
  for (int i = 0; i < this->getItemsCount(); i++) {
    if (this->getItem(i) == this->selectedMenuItem) {
      return i;
    }
  }
  // return 0;
}

MenuItem* MenuItemsContainer::getItem(int i) const {
  int count = 0;
  MenuNode *current = root;
  while (current->getNext() != root && count < i) {
    ++count;
    current = current->getNext();
  }
  return current->getItem();
}

int MenuItemsContainer::getItemsCount() const {
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
  int itemsCount = this->getItemsCount();

  if (this->selectedMenuItem == NULL && itemsCount) {
    this->selectedMenuItem = this->getItem(0);
  }

  if (this->tickNumber % this->handleTickFrequency == 0) {
    if (itemsCount) {
      for (int i = 0; i < itemsCount; i++) {
        bool handled = this->getItem(i)->handleTick();
        if (handled) {
          handledAction = true;
        }
      }
    }
  }
  ++this->tickNumber;

  if (this->actionsProvider.isToggleEditModeAction()) {
    if (this->isEditMode){
      this->isEditMode = false;
    } else {
      if (this->selectedMenuItem->shouldShowProgress()){
        this->renderer.renderProgress(*selectedMenuItem);
      }
      bool isEditable = this->selectedMenuItem->handleEditAction();
      this->isEditMode = isEditable;
    }
    handledAction = true;
  } else if (this->actionsProvider.isNextAction()) {
    if (this->isEditMode) {
      this->selectedMenuItem->handleNextAction();
    } else {
      this->selectedMenuItem = this->getItem((this->getSelectedItemIndex() + 1) % this->getItemsCount());
    }
    handledAction = true;
  } else if (this->actionsProvider.isPreviousAction()) {
    if (this->isEditMode) {
      this->selectedMenuItem->handlePreviousAction();
    } else {
      int previousIndex = (this->getSelectedItemIndex() - 1);
      if (previousIndex < 0) {
        previousIndex = this->getItemsCount() - 1;
      }
      this->selectedMenuItem = this->getItem(previousIndex);
    }
    handledAction = true;
  }

  if (handledAction || !this->rendered) {
    render();
    this->rendered = true;
    this->actionsProvider.afterActionHandler();
  }
}

MenuItemsContainer::~MenuItemsContainer() {
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
