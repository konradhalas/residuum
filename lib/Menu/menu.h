#ifndef MENU_H
#define MENU_H

#include "renderer.h"
#include "actionsprovider.h"
#include "items.h"

class MenuNode {
  public:
    MenuNode(MenuItem* item);
    ~MenuNode();
    MenuNode* getNext();
    MenuNode* getPrevious();
    MenuItem* getItem();
    void setNext(MenuNode *node);
    void setPrevious(MenuNode *node);
  private:
    MenuItem *item;
    MenuItem *parent;
    MenuNode *next;
    MenuNode *previous;
};

class MenuItemsContainer {
  public:
    MenuItemsContainer();
    ~MenuItemsContainer();
    void addItem(MenuItem *item);
    MenuItem* getItem(int i) const;
    int getItemsCount() const;

  private:
    MenuNode *root;
};

class Menu: public MenuItemsContainer {
  public:
    Menu(MenuRenderer &renderer, MenuActionsProvider &actionsProvider, int handleTickFrequency=1);
    void handle();
    int getSelectedItemIndex() const;
  private:
    void render();
    MenuItem *selectedMenuItem;
    MenuRenderer &renderer;
    MenuActionsProvider &actionsProvider;
    bool isEditMode;
    int tickNumber;
    int handleTickFrequency;
    bool rendered;
};

#endif
