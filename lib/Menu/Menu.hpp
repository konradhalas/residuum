#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

class MenuItem {
  public:
    MenuItem(String name, int value);
    String getName();
    int getValue();
    void setValue(int value);

  private:
    String name;
    int value;
};

class MenuNode {
  public:
    MenuNode(MenuItem *item);
    boolean hasNext();
    MenuNode* getNext();
    boolean hasPrevious();
    MenuNode* getPrevious();
    void setNext(MenuNode *node);
    void setPrevious(MenuNode *node);
    MenuItem* getItem();
  private:
    MenuItem *item;
    MenuNode *next = NULL;
    MenuNode *previous = NULL;
};

class Menu {
  public:
    Menu(Adafruit_PCD8544 & display, int selectButtonPin, int nextButtonPin);
    void addItem(String variable, int value);
    void render();
    void nextItem();
    void previousItem();
    void toggleSelectItem();
    void handle();
    void incrementSelectedItem();
  private:
    Adafruit_PCD8544 & display;
    int selectButtonPin;
    int nextButtonPin;
    MenuNode *currentNode = NULL;
    bool isItemSelected = false;

    MenuNode *root = NULL;
};
