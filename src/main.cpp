#ifndef UNIT_TEST

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "LCDMenu/lcdmenu.h"

#define FIRST_BUTTON_PIN 7
#define SECOND_BUTTON_PIN 13

#define LCD_LED_PIN 5
#define LCD_DC_PIN 8
#define LCD_CS_PIN 10
#define LCD_RST_PIN 9

#define BUTTONS_DELAY 500

class ChangeContrastCommand: public Command<IntegerValueMenuItem> {
  public:
    ChangeContrastCommand(Adafruit_PCD8544 &display): display(display) {
    }
    void run(const IntegerValueMenuItem &item) {
        display.setContrast(item.getValue());
    }
  private:
    Adafruit_PCD8544 &display;
};

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC_PIN, LCD_CS_PIN, LCD_RST_PIN);
LCDMenuRenderer renderer = LCDMenuRenderer(display);
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider(FIRST_BUTTON_PIN, SECOND_BUTTON_PIN, BUTTONS_DELAY);
Menu menu = Menu(renderer, actionsProvider);

void setup()   {
  Serial.begin(9600);

  int defaultContrast = 55;

  renderer.setup(LCD_LED_PIN, defaultContrast);

  menu.addItem(new IntegerValueMenuItem("CONTR", defaultContrast, new ChangeContrastCommand(display)));
  menu.addItem(new ActionMenuItem("START", NULL));
  menu.render();
}

void loop() {
  menu.handle();
}

#endif
