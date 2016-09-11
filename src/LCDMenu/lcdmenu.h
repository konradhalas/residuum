#ifndef LCD_MENU_H
#define LCD_MENU_H

#include <menu.h>

#include <Adafruit_PCD8544.h>

class LCDMenuRenderer: public MenuRenderer {
  public:
    LCDMenuRenderer(Adafruit_PCD8544 &display): display(display) {}
    void setup(int lcdLedPin, int contrast);
    void renderItem(const IntegerValueMenuItem &item, bool isSelected);
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
    ArduinoMenuActionsProvider(int firstButton, int secondButton, int buttonsDealy);
    bool isToggleEditModeAction();
    bool isNextAction();
    void afterActionHandler();
  private:
    int firstButton;
    int secondButton;
    int buttonsDealy;
};

#endif
