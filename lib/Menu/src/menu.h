#ifndef MENU_H
#define MENU_H

#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
typedef std::string String;
#endif

class MenuNode;
class MenuItem;

class MenuRenderer {
  public:
    virtual void renderItem(const MenuItem &item, bool isSelected) = 0;
    virtual void renderStart(bool isEditMode) = 0;
    virtual void renderFinish() = 0;
};

class MenuActionsProvider {
  public:
    virtual bool isToggleEditModeAction() = 0;
    virtual bool isNextAction() = 0;
    virtual void afterActionHandler() = 0;
};

class MenuItem {
  public:
    MenuItem(String name, int value);
    MenuItem(const MenuItem &item);
    String getName() const;
    int getValue() const;
    void setValue(int value);

  private:
    String name;
    int value;
};

class MenuNode {
  public:
    MenuNode(const MenuItem item);
    MenuNode* getNext();
    MenuNode* getPrevious();
    void setNext(MenuNode *node);
    void setPrevious(MenuNode *node);
    MenuItem & getItem();
  private:
    MenuItem item;
    MenuNode *next;
    MenuNode *previous;
};

class Menu {
  public:
    Menu(MenuRenderer & renderer, MenuActionsProvider & actionsProvider);
    void addItem(const MenuItem item);
    void render();
    void handle();
    MenuItem& getItem(int i) const;
    int getItemsCount() const;
  private:
    MenuNode *root;
    MenuNode *selectedNode;
    MenuRenderer &renderer;
    MenuActionsProvider &actionsProvider;
    bool isEditMode;
};

#endif
