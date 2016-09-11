#ifndef MENU_H
#define MENU_H

#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
typedef std::string String;
#endif

class MenuNode;
class IntegerValueMenuItem;
class ActionMenuItem;
class MenuItem;

class MenuRenderer {
  public:
    virtual void renderItem(const IntegerValueMenuItem &item, bool isSelected) = 0;
    virtual void renderItem(const ActionMenuItem &item, bool isSelected) = 0;
    virtual void renderStart(bool isEditMode) = 0;
    virtual void renderFinish() = 0;
    virtual int getItemsLimit() { return 0; };
};

class MenuActionsProvider {
  public:
    virtual bool isToggleEditModeAction() = 0;
    virtual bool isNextAction() = 0;
    virtual void afterActionHandler() = 0;
};

class MenuItem {
  public:
    virtual void renderDispatch(MenuRenderer &renderer, bool isSelected) = 0;
    virtual String getName() const = 0;
    virtual void handleNextAction() = 0;
    virtual bool handleEditAction() = 0;
    virtual ~MenuItem() {};
};

template <typename T>
class Command {
  public:
    virtual void run(const T &value) = 0;
};

class IntegerValueMenuItem : public MenuItem {
  public:
    IntegerValueMenuItem(String name, int value, Command<IntegerValueMenuItem> *onValueChangeCommand = NULL);
    IntegerValueMenuItem(const IntegerValueMenuItem &item);
    ~IntegerValueMenuItem() {};
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    String getName() const;
    void handleNextAction();
    bool handleEditAction();
    int getValue() const;
    void setValue(int value);
  private:
    String name;
    int value;
    Command<IntegerValueMenuItem> *onValueChangeCommand;
};

class ActionMenuItem: public MenuItem {
  public:
    ActionMenuItem(String name, Command<ActionMenuItem> *command);
    String getName() const;
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    void handleNextAction();
    bool handleEditAction();
  private:
    String name;
    Command<ActionMenuItem> *command;
};

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
    Menu(MenuRenderer &renderer, MenuActionsProvider &actionsProvider);
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
};

#endif
