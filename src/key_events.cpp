#include "key_events.h"
#include "layers.h"

void handle_synthetic_key_event(Key mappedKey, uint8_t keyState) {
    if (!key_toggled_on(keyState))
        return;

    if (mappedKey.flags & IS_CONSUMER) {
        ConsumerControl.press(mappedKey.rawKey);
    } else if (mappedKey.flags & IS_INTERNAL) {
        if (mappedKey.rawKey == LED_TOGGLE) {
            LEDControl.next_mode();
        }
    } else if (mappedKey.flags & IS_SYSCTL) {
        SystemControl.press(mappedKey.rawKey);
    }
}

custom_handler_t eventHandlers[HOOK_MAX];

void handle_key_event(Key mappedKey, byte row, byte col, uint8_t keyState) {
    if (!(keyState & INJECTED)) {
        mappedKey = Layer.lookup(row, col);
    }
    for (byte i = 0; eventHandlers[i] != NULL && i < HOOK_MAX; i++) {
        custom_handler_t handler = eventHandlers[i];
        if ((*handler)(mappedKey, row, col, keyState))
            return;
    }
}

bool handle_key_event_default(Key mappedKey, byte row, byte col, uint8_t keyState) {
    //for every newly pressed button, figure out what logical key it is and send a key down event
    // for every newly released button, figure out what logical key it is and send a key up event

    if ((mappedKey.flags & SWITCH_TO_KEYMAP
      || mappedKey.flags & SWITCH_TO_KEYMAP_MOMENTARY)) {
        handle_keymap_key_event(mappedKey, keyState);
    } else if (mappedKey.flags & SYNTHETIC) {
        handle_synthetic_key_event( mappedKey, keyState);
    } else if (key_is_pressed(keyState)) {
        press_key(mappedKey);
    } else if (key_toggled_off(keyState) && (keyState & INJECTED)) {
        release_key(mappedKey);
    }
    return true;
}

void press_key(Key mappedKey) {
    if (mappedKey.flags & SHIFT_HELD) {
        Keyboard.press(Key_LShift.rawKey);
    }
    if (mappedKey.flags & CTRL_HELD) {
        Keyboard.press(Key_LCtrl.rawKey);
    }
    if (mappedKey.flags & LALT_HELD) {
        Keyboard.press(Key_LAlt.rawKey);
    }
    if (mappedKey.flags & RALT_HELD) {
        Keyboard.press(Key_RAlt.rawKey);
    }
    if (mappedKey.flags & GUI_HELD) {
        Keyboard.press(Key_LGUI.rawKey);
    }
    Keyboard.press(mappedKey.rawKey);
}


void release_key(Key mappedKey) {
    if (mappedKey.flags & SHIFT_HELD) {
        Keyboard.release(Key_LShift.rawKey);
    }
    if (mappedKey.flags & CTRL_HELD) {
        Keyboard.release(Key_LCtrl.rawKey);
    }
    if (mappedKey.flags & LALT_HELD) {
        Keyboard.release(Key_LAlt.rawKey);
    }
    if (mappedKey.flags & RALT_HELD) {
        Keyboard.release(Key_RAlt.rawKey);
    }
    if (mappedKey.flags & GUI_HELD) {
        Keyboard.release(Key_LGUI.rawKey);
    }
    Keyboard.release(mappedKey.rawKey);
}


void handle_keymap_key_event(Key keymapEntry, uint8_t keyState) {
    if (keymapEntry.flags & SWITCH_TO_KEYMAP_MOMENTARY ) {
        if (key_toggled_on(keyState)) {
            if ( keymapEntry.rawKey == KEYMAP_NEXT) {
                Layer.next();
            } else if ( keymapEntry.rawKey == KEYMAP_PREVIOUS) {
                Layer.previous();
            } else {
                Layer.on(keymapEntry.rawKey);
            }
        }
        if (key_toggled_off(keyState)) {
            if ( keymapEntry.rawKey == KEYMAP_NEXT) {
                Layer.previous();
            } else if ( keymapEntry.rawKey == KEYMAP_PREVIOUS) {
                Layer.next();
            } else {
                Layer.off(keymapEntry.rawKey);
            }
        }

        // switch keymap and stay there
    } else if (key_toggled_on(keyState)) {
        Layer.on (keymapEntry.rawKey);
    }
}
