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

class ChangeContrastCommand: public Command<IntegerValueMenuItem> {
  public:
    ChangeContrastCommand(Adafruit_PCD8544 &display): display(display) {
    }
    void run(IntegerValueMenuItem &item) {
        display.setContrast(item.getValue());
    }
  private:
    Adafruit_PCD8544 &display;
};

class ToggleBacklightCommand: public Command<BoolValueMenuItem> {
  public:
    ToggleBacklightCommand(int pin): pin(pin) {}
    void run(BoolValueMenuItem &item) {
        analogWrite(this->pin, item.getValue() ? 255 : 0);
    }
  private:
    int pin;
};

#endif
