#ifndef MENU_RENDER_H
#define MENU_RENDER_H

class MenuNode;
class IntegerValueMenuItem;
class BoolValueMenuItem;
class ActionMenuItem;
class MenuItem;

class MenuRenderer {
  public:
    virtual void renderItem(const IntegerValueMenuItem &item, bool isSelected) = 0;
    virtual void renderItem(const BoolValueMenuItem &item, bool isSelected) = 0;
    virtual void renderItem(const ActionMenuItem &item, bool isSelected) = 0;
    virtual void renderStart(bool isEditMode) = 0;
    virtual void renderFinish() = 0;
    virtual int getItemsLimit() { return 0; };
};

#endif