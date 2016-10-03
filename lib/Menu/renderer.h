#ifndef MENU_RENDER_H
#define MENU_RENDER_H

class MenuNode;
class IntegerValueMenuItem;
class BoolValueMenuItem;
class ActionMenuItem;
class SubMenuItem;
class ParentMenuItem;
class MenuItem;

class MenuRenderer {
  public:
    virtual void renderItem(const IntegerValueMenuItem &item, bool isSelected) = 0;
    virtual void renderItem(const BoolValueMenuItem &item, bool isSelected) = 0;
    virtual void renderItem(const ActionMenuItem &item, bool isSelected) = 0;
    virtual void renderItem(const SubMenuItem &item, bool isSelected) = 0;
    virtual void renderItem(const ParentMenuItem &item, bool isSelected) = 0;
    virtual void renderStart(bool isEditMode) = 0;
    virtual void renderProgress(const MenuItem &item) = 0;
    virtual void renderFinish() = 0;
    virtual int getItemsLimit() { return 0; };
};

#endif
