#include "Storage.h"

static union {
  struct {
    bool    firstBoot:1;
    bool    useEEPROMKeymap:1;
    uint8_t maxKeymaps:3;
    uint8_t currentKeymaps:3;

    uint8_t defaultKeymap:5;
    uint8_t __reserved:3;
  };
  uint16_t all;
} eepromMeta;

static uint8_t keymapLimit;

Storage_::Storage_(void) {
}

void
Storage_::setup(uint8_t keymapLimit_) {
    keymapLimit = keymapLimit_;

    EEPROM.get(0, eepromMeta.all);

    // If this is the first boot, set some sane defaults, and return. EEPROM comes
    // filled with 255, so the firstBoot bit will be set by default.
    //
    // We do not write it back, to save a write. On next boot, until anything
    // changes in the EEPROM, we'll do this reinit thing, to save on writes.
    if (eepromMeta.firstBoot) {
        eepromMeta.firstBoot = false;
        eepromMeta.useEEPROMKeymap = false;
        eepromMeta.maxKeymaps = EEPROM_KEYMAP_SIZE;
        eepromMeta.currentKeymaps = 0;

        eepromMeta.defaultKeymap = 0;
        eepromMeta.__reserved = 0;

        return;
    }

    // Sanity checks...
    if (eepromMeta.useEEPROMKeymap) {
        if (eepromMeta.currentKeymaps > eepromMeta.maxKeymaps)
            eepromMeta.currentKeymaps = eepromMeta.maxKeymaps;

        if (eepromMeta.defaultKeymap >= eepromMeta.currentKeymaps)
            eepromMeta.defaultKeymap = 0;
        if (eepromMeta.defaultKeymap >= eepromMeta.maxKeymaps)
            eepromMeta.defaultKeymap = 0;

        if (eepromMeta.currentKeymaps == 0)
            eepromMeta.useEEPROMKeymap = false;
    }

    if (!eepromMeta.useEEPROMKeymap) {
        if (eepromMeta.defaultKeymap >= keymapLimit)
            eepromMeta.defaultKeymap = 0;
    }

    // Update things back, so we're in sync.
    // Most of the time, this will not update anything.
    EEPROM.put(0, eepromMeta.all);
}

uint8_t
Storage_::defaultKeymap(void) {
    return eepromMeta.defaultKeymap;
}

void
Storage_::defaultKeymap(uint8_t keymap) {
    if (!eepromMeta.useEEPROMKeymap && keymap >= keymapLimit)
        return;
    if (eepromMeta.useEEPROMKeymap && keymap >= eepromMeta.currentKeymaps)
        return;

    eepromMeta.defaultKeymap = keymap;
    EEPROM.put(0, eepromMeta.all);
}

bool
Storage_::useEEPROMKeymap(void) {
    return eepromMeta.useEEPROMKeymap;
}

void
Storage_::useEEPROMKeymap(bool value) {
    eepromMeta.useEEPROMKeymap = value;
    EEPROM.put(0, eepromMeta.all);
}

uint8_t
Storage_::currentKeymaps(void) {
    return eepromMeta.currentKeymaps;
}

void
Storage_::currentKeymaps(uint8_t keymapLimit) {
  if (keymapLimit >= eepromMeta.maxKeymaps)
    keymapLimit = eepromMeta.maxKeymaps;

  eepromMeta.currentKeymaps = keymapLimit;
  EEPROM.put(0, eepromMeta.all);
}

Storage_ Storage;
