#ifndef MENU_H
#define MENU_H

#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
typedef std::string String;
#endif

class Menu;

class MenuRenderer {
  public:
    virtual void render(Menu &menu) = 0;
};

class MenuActionsProvider {
  public:
    virtual bool isSelectAction() = 0;
    virtual bool isNextAction() = 0;
    virtual void afterActionHandler() = 0;
};

class MenuItem {
  public:
    MenuItem(String name, int value);
    String getName();
    int getValue();
    void setValue(int value);

  private:
    String name;
    int value;
};

class MenuNode {
  public:
    MenuNode(MenuItem *item);
    bool hasNext();
    MenuNode* getNext();
    bool hasPrevious();
    MenuNode* getPrevious();
    void setNext(MenuNode *node);
    void setPrevious(MenuNode *node);
    MenuItem* getItem();
  private:
    MenuItem *item;
    MenuNode *next;
    MenuNode *previous;
};

class Menu {
  public:
    Menu(MenuRenderer & renderer, MenuActionsProvider & actionsProvider);
    void addItem(String variable, int value);
    void render();
    void nextItem();
    void previousItem();
    void toggleSelectItem();
    void handle();
    void incrementSelectedItem();
    MenuItem& getItem(int i);
    int getItemsCount();
  private:
    MenuNode *currentNode;
    bool isItemSelected;
    MenuNode *root;
    MenuRenderer &renderer;
    MenuActionsProvider &actionsProvider;
};

#endif
