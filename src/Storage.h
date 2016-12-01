#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include "keymap_metadata.h"

#define EEPROM_KEYMAP_SIZE 4
#define EEPROM_KEYMAP_START (1023 - (EEPROM_KEYMAP_SIZE * 128))
#define EEPROM_SAFE_RANGE_START 2
#define EEPROM_SAFE_RANGE_END (EEPROM_KEYMAP_START - 1)

class Storage_ {
  private:

  public:
    Storage_(void);

    static void setup(uint8_t keymapLimit);

    static uint8_t defaultKeymap(void);
    static void defaultKeymap(uint8_t keymap);

    static bool useEEPROMKeymap(void);
    static void useEEPROMKeymap(bool value);

    static uint8_t currentKeymaps(void);
    static void currentKeymaps(uint8_t keymapLimit);
};

extern Storage_ Storage;
