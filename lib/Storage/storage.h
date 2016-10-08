#ifndef STORAGE_H
#define STORAGE_H

#include <EEPROM.h>

template <class T>
class Storage {
  public:

    static void save(T data) {
      for (unsigned int t=0; t < sizeof(data); t++) {
        EEPROM.write(t, *((char*)&data + t));
      }
    }

    static T load() {
      T data;
      for (unsigned int t=0; t < sizeof(data); t++) {
        *((char*)&data + t) = EEPROM.read(t);
      }
      return data;
    }
};

#endif
