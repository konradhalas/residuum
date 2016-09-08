#ifndef UNIT_TEST

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "menu.h"

#define LCD_LED_PIN 5
#define FIRST_BUTTON_PIN 7
#define SECOND_BUTTON_PIN 13
#define LED_PIN 11

#define BUTTONS_DELAY 500

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 10, 9);

class LCDMenuRenderer: public MenuRenderer {
  public:
    LCDMenuRenderer(Adafruit_PCD8544 &display): display(display) {

    }
    void render(const Menu &menu) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(0, 0);
      for (int i = 0; i < menu.getItemsCount(); i++) {
        MenuItem &item = menu.getItem(i);
        display.println(item.getName() + " = " + item.getValue());
      }
      display.display();
    }
  private:
    Adafruit_PCD8544 &display;
};

class ArduinoMenuActionsProvider: public MenuActionsProvider {
  public:
    ArduinoMenuActionsProvider() {
      pinMode(SECOND_BUTTON_PIN, INPUT);
      pinMode(FIRST_BUTTON_PIN, INPUT);
    }
    bool isSelectAction() {
      return digitalRead(SECOND_BUTTON_PIN) == HIGH;
    };
    bool isNextAction() {
      return digitalRead(FIRST_BUTTON_PIN) == HIGH;
    };
    void afterActionHandler() {
      delay(BUTTONS_DELAY);
    };
};

LCDMenuRenderer renderer = LCDMenuRenderer(display);
ArduinoMenuActionsProvider actionsProvider = ArduinoMenuActionsProvider();
Menu menu = Menu(renderer, actionsProvider);

void initializeDisplay() {
  pinMode(LCD_LED_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  analogWrite(LCD_LED_PIN, 255);

  display.begin();
  display.setContrast(60);
}

void setup()   {
  Serial.begin(9600);

  initializeDisplay();

  menu.addItem(MenuItem("VAL A", 10));
  menu.addItem(MenuItem("VAL B", 20));
  menu.addItem(MenuItem("VALUE C", 100));
  menu.render();
}

void loop() {
  menu.handle();
}

#endif
