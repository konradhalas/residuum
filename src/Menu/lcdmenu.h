#ifndef LCD_MENU_H
#define LCD_MENU_H

#include <menu.h>

#include <Adafruit_PCD8544.h>

class LCDMenuRenderer: public MenuRenderer {
  public:
    LCDMenuRenderer(Adafruit_PCD8544 &display);
    void setup(int lcdLedPin, int contrast);
    void renderItem(const IntegerValueMenuItem &item, bool isSelected);
    void renderItem(const BoolValueMenuItem &item, bool isSelected);
    void renderItem(const ActionMenuItem &item, bool isSelected);
    void renderStart(bool isEditMode);
    void renderFinish();
    int getItemsLimit() { return 6; };
  private:
    String getItemPrefix(bool isSelected);
    Adafruit_PCD8544 &display;
    bool isEditMode;
};

class ArduinoMenuActionsProvider: public MenuActionsProvider {
  public:
    ArduinoMenuActionsProvider(int nextButton, int editButton, int previousButton, int buttonsDealy);
    bool isToggleEditModeAction();
    bool isNextAction();
    bool isPreviousAction();
    void afterActionHandler();
  private:
    int nextButton;
    int editButton;
    int previousButton;
    int buttonsDealy;
};

#endif
