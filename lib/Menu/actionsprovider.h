#ifndef MENU_ACTIONS_PROVIDER_H
#define MENU_ACTIONS_PROVIDER_H

class MenuActionsProvider {
  public:
    virtual bool isToggleEditModeAction() = 0;
    virtual bool isNextAction() = 0;
    virtual bool isPreviousAction() = 0;
    virtual void afterActionHandler() = 0;
};

#endif
