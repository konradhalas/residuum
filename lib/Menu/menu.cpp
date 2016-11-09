#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
typedef std::string String;
#endif

#include "menu.h"

Menu::Menu(MenuRenderer & renderer, MenuActionsProvider & actionsProvider, int handleTickFrequency) : MenuItemsContainer(), renderer(renderer), actionsProvider(actionsProvider), handleTickFrequency(handleTickFrequency) {
  this->selectedMenuItem = NULL;
  this->isEditMode = false;
  this->tickNumber = 0;
  this->rendered = false;
  this->container = this;
}

void Menu::render() {
  this->renderer.renderStart(this->isEditMode);

  int selectedItemIndex = this->getSelectedItemIndex();
  int itemsCount = this->container->getItemsCount();

  int startItemIndex, endItemIndex;
  if (this->renderer.getItemsLimit() == 0) {
    startItemIndex = 0;
    endItemIndex = itemsCount - 1;
  } else {
    startItemIndex = (selectedItemIndex / this->renderer.getItemsLimit()) * this->renderer.getItemsLimit();
    endItemIndex = startItemIndex + this->renderer.getItemsLimit() - 1;
  }
  for (int i = startItemIndex; i <= endItemIndex && i < itemsCount; i++) {
    this->container->getItem(i)->renderDispatch(this->renderer, selectedItemIndex == i);
  }
  this->renderer.renderFinish();
}

int Menu::getSelectedItemIndex() const {
  if (!this->container->getItemsCount()) {
    return -1;
  }
  for (int i = 0; i < this->container->getItemsCount(); i++) {
    if (this->container->getItem(i) == this->selectedMenuItem) {
      return i;
    }
  }
  return 0;
}

void Menu::handle() {
  bool handledAction = false;
  bool handledTick = false;
  int itemsCount = this->container->getItemsCount();

  if (this->selectedMenuItem == NULL && itemsCount) {
    this->selectedMenuItem = this->container->getItem(0);
  }

  if (this->tickNumber % this->handleTickFrequency == 0) {
    if (itemsCount) {
      for (int i = 0; i < itemsCount; i++) {
        bool handled = this->container->getItem(i)->handleTick();
        if (handled) {
          handledTick = true;
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
      bool isEditable = this->selectedMenuItem->handleEditAction(*this);
      this->isEditMode = isEditable;
    }
    handledAction = true;
  } else if (this->actionsProvider.isNextAction()) {
    if (this->isEditMode) {
      this->selectedMenuItem->handleNextAction();
    } else {
      this->selectedMenuItem = this->container->getItem((this->getSelectedItemIndex() + 1) % this->container->getItemsCount());
    }
    handledAction = true;
  } else if (this->actionsProvider.isPreviousAction()) {
    if (this->isEditMode) {
      this->selectedMenuItem->handlePreviousAction();
    } else {
      int previousIndex = (this->getSelectedItemIndex() - 1);
      if (previousIndex < 0) {
        previousIndex = this->container->getItemsCount() - 1;
      }
      this->selectedMenuItem = this->container->getItem(previousIndex);
    }
    handledAction = true;
  }

  if (handledAction || handledTick || !this->rendered) {
    render();
    this->rendered = true;
    if (handledAction) {
        this->actionsProvider.afterActionHandler();
    }
  }
}

void Menu::goTo(MenuItemsContainer *container, MenuItem *menuItemToSelect) {
  this->container = container;
  this->selectedMenuItem = menuItemToSelect;
}
