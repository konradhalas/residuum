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
    MenuNode *next;
    MenuNode *previous;
};

class Menu {
  public:
    Menu(MenuRenderer &renderer, MenuActionsProvider &actionsProvider, int handleTickFrequency=1);
    void addItem(MenuItem *item);
    void render();
    void handle();
    MenuItem* getItem(int i) const;
    int getItemsCount() const;
    int getSelectedItemIndex() const;
    ~Menu();
  private:
    MenuNode *root;
    MenuNode *selectedNode;
    MenuRenderer &renderer;
    MenuActionsProvider &actionsProvider;
    bool isEditMode;
    int tickNumber;
    int handleTickFrequency;
};

#endif
