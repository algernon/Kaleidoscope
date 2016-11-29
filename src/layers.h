#pragma once

#include <Arduino.h>
#include "key_defs.h"

class Layer_ {
  public:
    Layer_(void);

    static Key lookup(byte row, byte col);
    static void on(uint8_t layer);
    static void off(uint8_t layer);
    static void move(uint8_t layer);

    static uint8_t top(void);
    static void next(void);
    static void previous(void);

    static boolean isOn(uint8_t layer);

    static void defaultLayer(uint8_t layer);
    static uint8_t defaultLayer(void);

    static uint32_t getLayerState(void);
};

extern Layer_ Layer;
