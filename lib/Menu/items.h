#ifndef MENU_ITEMS_H
#define MENU_ITEMS_H

#ifdef ARDUINO
#include <WString.h>
#else
#include <string>
typedef std::string String;
#endif

#include "renderer.h"
#include "container.h"

class Menu;

class MenuItem {
  public:
    MenuItem(String name) : name(name) {};
    virtual void renderDispatch(MenuRenderer &renderer, bool isSelected) = 0;
    virtual void handleNextAction() = 0;
    virtual void handlePreviousAction() = 0;
    virtual bool handleEditAction(Menu &menu) = 0;
    virtual bool handleTick() { return false; }
    virtual bool shouldShowProgress() { return false; }
    virtual ~MenuItem() {};
    String getName() const { return this->name; }
  private:
    String name;
};

template <typename T>
class Command {
  public:
    virtual void run(T &value) = 0;
};

template <typename T, typename C>
class ValueMenuItem: public MenuItem {
  public:
    ValueMenuItem(String name, T value, C *valueChangedCommand = NULL, C *tickHandleCommand = NULL): MenuItem(name), value(value), valueChangedCommand(valueChangedCommand), tickHandleCommand(tickHandleCommand) {}
    T getValue() const { return value; };
    void setValue(T value) { this->value = value; };
    bool handleEditAction(Menu &menu) { return this->valueChangedCommand != NULL; };
    void handleNextAction() {
      this->updateValueOnNextAction();
      if (this->valueChangedCommand != NULL) {
        this->dispatchCommandRun(this->valueChangedCommand);
      }
    };
    void handlePreviousAction() {
      this->updateValueOnPreviousAction();
      if (this->valueChangedCommand != NULL) {
        this->dispatchCommandRun(this->valueChangedCommand);
      }
    };
    bool handleTick() {
      if (this->tickHandleCommand != NULL) {
        this->dispatchCommandRun(this->tickHandleCommand);
        return true;
      }
      return false;
    };
    virtual void updateValueOnNextAction() = 0;
    virtual void updateValueOnPreviousAction() = 0;
    virtual void dispatchCommandRun(C *command) = 0;
  private:
    T value;
    C *valueChangedCommand;
    C *tickHandleCommand;
};

class IntegerValueMenuItem: public ValueMenuItem<int, Command<IntegerValueMenuItem> > {
  public:
    IntegerValueMenuItem(String name, int value, Command<IntegerValueMenuItem> *valueChangedCommand = NULL, Command<IntegerValueMenuItem> *tickHandleCommand = NULL);
    ~IntegerValueMenuItem() {};
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    void updateValueOnNextAction();
    void updateValueOnPreviousAction();
    void dispatchCommandRun(Command<IntegerValueMenuItem> *command);
};

class BoolValueMenuItem: public ValueMenuItem<bool, Command<BoolValueMenuItem> > {
  public:
    BoolValueMenuItem(String name, bool value, Command<BoolValueMenuItem> *valueChangedCommand = NULL, Command<BoolValueMenuItem> *tickHandleCommand = NULL);
    ~BoolValueMenuItem() {};
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    void updateValueOnNextAction();
    void updateValueOnPreviousAction();
    void dispatchCommandRun(Command<BoolValueMenuItem> *command);
};

class FloatValueMenuItem: public ValueMenuItem<float, Command<FloatValueMenuItem> > {
  public:
    FloatValueMenuItem(String name, float value, int base, Command<FloatValueMenuItem> *valueChangedCommand = NULL, Command<FloatValueMenuItem> *tickHandleCommand = NULL);
    ~FloatValueMenuItem() {};
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    void updateValueOnNextAction();
    void updateValueOnPreviousAction();
    void dispatchCommandRun(Command<FloatValueMenuItem> *command);
    int getBase() const;
  private:
    int base;
};

class ActionMenuItem: public MenuItem {
  public:
    ActionMenuItem(String name, Command<ActionMenuItem> *command);
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    void handleNextAction();
    void handlePreviousAction();
    bool handleEditAction(Menu &menu);
    bool shouldShowProgress();
  private:
    Command<ActionMenuItem> *command;
};

class SubMenuItem: public MenuItem, public MenuItemsContainer {
  public:
    SubMenuItem(String name, MenuItemsContainer *parent);
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    void handleNextAction();
    void handlePreviousAction();
    bool handleEditAction(Menu &menu);
};

class ParentMenuItem: public MenuItem {
  public:
    ParentMenuItem(MenuItemsContainer *parent, SubMenuItem *subMenuItem);
    void renderDispatch(MenuRenderer &renderer, bool isSelected);
    void handleNextAction();
    void handlePreviousAction();
    bool handleEditAction(Menu &menu);
  private:
    MenuItemsContainer *parent;
    SubMenuItem *subMenuItem;
};

#endif
