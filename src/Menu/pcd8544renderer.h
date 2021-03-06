#ifndef LCD_MENU_H
#define LCD_MENU_H

#include "menu.h"

#include <Adafruit_PCD8544.h>

class PCD8544MenuRenderer: public MenuRenderer {
  public:
    PCD8544MenuRenderer(Adafruit_PCD8544 &display);
    void setup(int lcdLedPin, int contrast, bool backlight);
    void renderItem(const IntegerValueMenuItem &item, bool isSelected);
    void renderItem(const BoolValueMenuItem &item, bool isSelected);
    void renderItem(const FloatValueMenuItem &item, bool isSelected);
    void renderItem(const ActionMenuItem &item, bool isSelected);
    void renderItem(const SubMenuItem &item, bool isSelected);
    void renderItem(const ParentMenuItem &item, bool isSelected);
    void renderStart(bool isEditMode);
    void renderProgress(const MenuItem &item);
    void renderFinish();
    int getItemsLimit() { return 6; };
  private:
    String getItemPrefix(bool isSelected);
    Adafruit_PCD8544 &display;
    bool isEditMode;
};

#endif
