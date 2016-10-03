#ifndef MENU_ITEMS_CONTAINER_H
#define MENU_ITEMS_CONTAINER_H

#include "renderer.h"
#include "actionsprovider.h"

class MenuItem;

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

#endif
