#ifndef LCD_MENU_H
#define LCD_MENU_H

#include <menu.h>

#include <Adafruit_PCD8544.h>

class LCDMenuRenderer: public MenuRenderer {
  public:
    LCDMenuRenderer(Adafruit_PCD8544 &display): display(display) {}
    void render(MenuNode *node);
    void setup(int lcdLedPin);

  private:
    Adafruit_PCD8544 &display;
};

class ArduinoMenuActionsProvider: public MenuActionsProvider {
  public:
    ArduinoMenuActionsProvider(int firstButton, int secondButton, int buttonsDealy);
    bool isSelectAction();
    bool isNextAction();
    void afterActionHandler();
  private:
    int firstButton;
    int secondButton;
    int buttonsDealy;
};

#endif
