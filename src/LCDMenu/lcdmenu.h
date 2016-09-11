#ifndef LCD_MENU_H
#define LCD_MENU_H

#include <menu.h>

#include <Adafruit_PCD8544.h>

class LCDMenuRenderer: public MenuRenderer {
  public:
    LCDMenuRenderer(Adafruit_PCD8544 &display): display(display) {}
    void setup(int lcdLedPin);
    void renderItem(const IntegerValueMenuItem &item, bool isSelected);
    void renderStart(bool isEditMode);
    void renderFinish();
  private:
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
