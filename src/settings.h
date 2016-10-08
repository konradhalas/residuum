#ifndef SETTINGS_H
#define SETTINGS_H

#include "consts.h"

struct Settings {
  Settings(int lcdContrast=LCD_CONTRAST, bool lcdBakclight=LCD_BAKCLIGHT): lcdContrast(lcdContrast), lcdBakclight(lcdBakclight) {}
  int lcdContrast;
  bool lcdBakclight;
};

#endif
