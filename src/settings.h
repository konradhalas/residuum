#ifndef SETTINGS_H
#define SETTINGS_H

#include "consts.h"

struct Settings {
  Settings(int lcdContrast=LCD_CONTRAST, bool lcdBakclight=LCD_BAKCLIGHT, float followerKp=FOLLOWER_KP, int followerKd=FOLLOWER_KD, int followTimeout=FOLLOW_TIMEOUT, int motorsBaseSpeed=BASE_MOTOR_SPEED): lcdContrast(lcdContrast), lcdBakclight(lcdBakclight), followerKp(followerKp), followerKd(followerKd), followTimeout(followTimeout), motorsBaseSpeed(motorsBaseSpeed) {}
  int lcdContrast;
  bool lcdBakclight;
  float followerKp;
  int followerKd;
  int followTimeout;
  int motorsBaseSpeed;
};

#endif
