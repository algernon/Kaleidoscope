#include "KeyboardioFirmware.h"

Keyboardio_::Keyboardio_(void) {
    memset(eventHandlers, 0, HOOK_MAX * sizeof(custom_handler_t));
    memset(loopHooks, 0, HOOK_MAX * sizeof(custom_handler_t));
}

void
Keyboardio_::setup(const byte keymap_count) {
    event_handler_hook_add (handle_key_event_default);
    wdt_disable();
    delay(100);
    Keyboard.begin();
    KeyboardHardware.setup();
    LEDControl.setup();
    Storage.setup(keymap_count);

    temporary_keymap = primary_keymap = Storage.defaultKeymap();
}

custom_loop_t loopHooks[HOOK_MAX];

void
Keyboardio_::loop(void) {
    KeyboardHardware.scan_matrix();
    LEDControl.update();
    Keyboard.sendReport();
    Keyboard.releaseAll();

    for (byte i = 0; loopHooks[i] != NULL && i < HOOK_MAX; i++) {
      custom_loop_t hook = loopHooks[i];
      (*hook)();
    }
}

