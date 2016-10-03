#ifndef MENU_H
#define MENU_H

#include "renderer.h"
#include "actionsprovider.h"
#include "items.h"

class Menu: public MenuItemsContainer {
  public:
    Menu(MenuRenderer &renderer, MenuActionsProvider &actionsProvider, int handleTickFrequency=1);
    void handle();
    void goTo(MenuItemsContainer *container, MenuItem *menuItemToSelect);
  private:
    void render();
    int getSelectedItemIndex() const;
    MenuItemsContainer *container;
    MenuItem *selectedMenuItem;
    MenuRenderer &renderer;
    MenuActionsProvider &actionsProvider;
    bool isEditMode;
    int tickNumber;
    int handleTickFrequency;
    bool rendered;
};

#endif
