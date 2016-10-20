#ifndef SETTINGS_H
#define SETTINGS_H

#include "consts.h"

struct Settings {
  Settings(int lcdContrast=LCD_CONTRAST, bool lcdBakclight=LCD_BAKCLIGHT, float followerKp=FOLLOWER_KP, float followerKd=FOLLOWER_KD, int followTimeout=FOLLOW_TIMEOUT, int motorsBaseSpeed=BASE_MOTOR_SPEED): lcdContrast(lcdContrast), lcdBakclight(lcdBakclight), followerKp(followerKp), followerKd(followerKd), followTimeout(followTimeout), motorsBaseSpeed(motorsBaseSpeed) {}
  int lcdContrast;
  bool lcdBakclight;
  float followerKp;
  float followerKd;
  int followTimeout;
  int motorsBaseSpeed;
};

#endif
