#ifndef ARDUINO_MENU_ACTIONS_PROVIDER_H
#define ARDUINO_MENU_ACTIONS_PROVIDER_H

#include <actionsprovider.h>

class ArduinoMenuActionsProvider: public MenuActionsProvider {
  public:
    ArduinoMenuActionsProvider(int nextButton, int editButton, int previousButton, int actionLedPin, int buttonsDealy);
    bool isToggleEditModeAction();
    bool isNextAction();
    bool isPreviousAction();
    void afterActionHandler();
  private:
    int nextButton;
    int editButton;
    int previousButton;
    int actionLedPin;
    int buttonsDealy;
};

#endif
