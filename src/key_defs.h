#pragma once


#include "HIDTables.h"
typedef union Key_ {

    struct {
        uint8_t flags;
        uint8_t keyCode;
    };
    uint16_t raw;

    inline bool operator==(uint16_t rhs) { return this->raw == rhs; };
    inline bool operator==(const Key_ rhs) { return this->raw == rhs.raw; };
    inline Key_& operator=(uint16_t raw) { this->raw = raw; return *this; };
    inline bool operator!=(const Key_& rhs) { return !(*this == rhs); };
    inline bool operator>=(uint16_t raw) { return this->raw >= raw; };
    inline bool operator<=(uint16_t raw) { return this->raw <= raw; };
    inline bool operator>(uint16_t raw) { return this->raw > raw; };
    inline bool operator<(uint16_t raw) { return this->raw < raw; };
    inline bool operator>=(const Key_& other) { return this->raw >= other.raw; };
    inline bool operator<=(const Key_& other) { return this->raw <= other.raw; };
    inline bool operator>(const Key_& other) { return this->raw > other.raw; };
    inline bool operator<(const Key_& other) { return this->raw < other.raw; };
} Key;



#define KEY_FLAGS         B00000000
#define CTRL_HELD         B00000001
#define LALT_HELD         B00000010
#define RALT_HELD         B00000100
#define SHIFT_HELD        B00001000
#define GUI_HELD          B00010000
#define SYNTHETIC         B01000000
#define RESERVED          B10000000

#define LCTRL(k)  ((Key) { k.flags | CTRL_HELD, k.keyCode })
#define LALT(k)   ((Key) { k.flags | LALT_HELD, k.keyCode })
#define RALT(k)   ((Key) { k.flags | RALT_HELD, k.keyCode })
#define LSHIFT(k) ((Key) { k.flags | SHIFT_HELD, k.keyCode })
#define LGUI(k)   ((Key) { k.flags | GUI_HELD, k.keyCode })

// we assert that synthetic keys can never have keys held, so we reuse the _HELD bits
#define IS_SYSCTL                  B00000001
#define IS_CONSUMER                B00000010
#define SWITCH_TO_KEYMAP 		       B00000100
#define IS_INTERNAL                B00001000

#define MOMENTARY_OFFSET 42

// IS_INTERNAL key table:

#define LED_TOGGLE   B00000001 // Synthetic, internal


#define KEYMAP_0     0
#define KEYMAP_1     1
#define KEYMAP_2     2
#define KEYMAP_3     3
#define KEYMAP_4     4
#define KEYMAP_5     5
#define KEYMAP_6     6
#define KEYMAP_7     7


#define KEYMAP_PREVIOUS  33
#define KEYMAP_NEXT      34


#define Key_NoKey (Key){ KEY_FLAGS,0 }
#define Key_skip (Key){ KEY_FLAGS,0 }
#define Key_Transparent (Key){ .raw = 0xffff }
#define ___ Key_Transparent
#define XXX Key_NoKey


#define Key_powerDown (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_POWER_DOWN }
#define Key_sleep (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_SLEEP }
#define Key_wakeup (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_WAKEUP }
#define Key_coldRestart (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_COLD_RESTART }
#define Key_warmRestart (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_WARM_RESTART }
#define Key_dock (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DOCK }
#define Key_undock (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_UNDOCK }
#define Key_speakerMute (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_SPEAKER_MUTE }
#define Key_hibernate (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_HIBERNATE }
#define Key_displayInvert (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DISPLAY_INVERT }
#define Key_displayInternal (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DISPLAY_INTERNAL }
#define Key_displayExternal (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DISPLAY_EXTERNAL }
#define Key_displayBoth (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DISPLAY_BOTH }
#define Key_displayDual (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DISPLAY_DUAL }
#define Key_displayToggle (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DISPLAY_TOGGLE_INT_EXT
#define Key_displaySwap (Key) {KEY_FLAGS | SYNTHETIC|IS_SYSCTL,HID_SYSTEM_DISPLAY_SWAP }


#define Key_volumeMute (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_MUTE}
#define Key_volumeUp (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_VOLUME_INCREMENT }
#define Key_volumeDown (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_VOLUME_DECREMENT }
#define Key_playPause (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_PLAY_SLASH_PAUSE}
#define Key_stop (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_STOP}
#define Key_prevTrack (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_SCAN_PREVIOUS_TRACK}
#define Key_nextTrack (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_SCAN_NEXT_TRACK}
#define Key_Eject (Key) {KEY_FLAGS | SYNTHETIC|IS_CONSUMER, HID_CONSUMER_EJECT}


#define Key_LCtrl (Key){ KEY_FLAGS, HID_KEYBOARD_LEFT_CONTROL }
#define Key_LShift (Key){ KEY_FLAGS, HID_KEYBOARD_LEFT_SHIFT }
#define Key_LAlt (Key){ KEY_FLAGS, HID_KEYBOARD_LEFT_ALT }
#define Key_LGUI (Key){ KEY_FLAGS, HID_KEYBOARD_LEFT_GUI }
#define Key_RCtrl (Key){ KEY_FLAGS, HID_KEYBOARD_RIGHT_CONTROL }
#define Key_RShift (Key){ KEY_FLAGS, HID_KEYBOARD_RIGHT_SHIFT }
#define Key_RAlt (Key){ KEY_FLAGS, HID_KEYBOARD_RIGHT_ALT }
#define Key_RGUI (Key){ KEY_FLAGS, HID_KEYBOARD_RIGHT_GUI }

#define Key_UpArrow (Key){ KEY_FLAGS, HID_KEYBOARD_UP_ARROW }
#define Key_DnArrow (Key){ KEY_FLAGS, HID_KEYBOARD_DOWN_ARROW }
#define Key_LArrow (Key){ KEY_FLAGS, HID_KEYBOARD_LEFT_ARROW  }
#define Key_RArrow (Key){ KEY_FLAGS, HID_KEYBOARD_RIGHT_ARROW}
#define Key_Return (Key){ KEY_FLAGS, HID_KEYBOARD_RETURN }
#define Key_Esc (Key){ KEY_FLAGS, HID_KEYBOARD_ESCAPE }
#define Key_Backspace (Key){ KEY_FLAGS, HID_KEYBOARD_DELETE }
#define Key_Tab (Key){ KEY_FLAGS, HID_KEYBOARD_TAB }
#define Key_Insert (Key){ KEY_FLAGS, HID_KEYBOARD_INSERT }
#define Key_Delete (Key){ KEY_FLAGS, HID_KEYBOARD_DELETE_FORWARD }
#define Key_PageUp (Key){ KEY_FLAGS, HID_KEYBOARD_PAGE_UP }
#define Key_PageDn (Key){ KEY_FLAGS, HID_KEYBOARD_PAGE_DOWN }
#define Key_Home (Key){ KEY_FLAGS, HID_KEYBOARD_HOME }
#define Key_End (Key){ KEY_FLAGS, HID_KEYBOARD_END }


#define Key_CapsLock (Key){ KEY_FLAGS, HID_KEYBOARD_CAPS_LOCK }

#define Key_F1 (Key){ KEY_FLAGS, HID_KEYBOARD_F1 }
#define Key_F2 (Key){ KEY_FLAGS, HID_KEYBOARD_F2 }
#define Key_F3 (Key){ KEY_FLAGS, HID_KEYBOARD_F3 }
#define Key_F4 (Key){ KEY_FLAGS, HID_KEYBOARD_F4 }
#define Key_F5 (Key){ KEY_FLAGS, HID_KEYBOARD_F5 }
#define Key_F6 (Key){ KEY_FLAGS, HID_KEYBOARD_F6 }
#define Key_F7 (Key){ KEY_FLAGS, HID_KEYBOARD_F7 }
#define Key_F8 (Key){ KEY_FLAGS, HID_KEYBOARD_F8 }
#define Key_F9 (Key){ KEY_FLAGS, HID_KEYBOARD_F9 }
#define Key_F10 (Key){ KEY_FLAGS, HID_KEYBOARD_F10 }
#define Key_F11 (Key){ KEY_FLAGS, HID_KEYBOARD_F11 }
#define Key_F12 (Key){ KEY_FLAGS, HID_KEYBOARD_F12 }
#define Key_F13 (Key){ KEY_FLAGS, HID_KEYBOARD_F13 }
#define Key_F14 (Key){ KEY_FLAGS, HID_KEYBOARD_F14 }
#define Key_F15 (Key){ KEY_FLAGS, HID_KEYBOARD_F15 }
#define Key_F16 (Key){ KEY_FLAGS, HID_KEYBOARD_F16 }
#define Key_F17 (Key){ KEY_FLAGS, HID_KEYBOARD_F17 }
#define Key_F18 (Key){ KEY_FLAGS, HID_KEYBOARD_F18 }
#define Key_F19 (Key){ KEY_FLAGS, HID_KEYBOARD_F19 }
#define Key_F20 (Key){ KEY_FLAGS, HID_KEYBOARD_F20 }
#define Key_F21 (Key){ KEY_FLAGS, HID_KEYBOARD_F21 }
#define Key_F22 (Key){ KEY_FLAGS, HID_KEYBOARD_F22 }
#define Key_F23 (Key){ KEY_FLAGS, HID_KEYBOARD_F23 }
#define Key_F24 (Key){ KEY_FLAGS, HID_KEYBOARD_F24 }




#define Key_1 (Key){ KEY_FLAGS, HID_KEYBOARD_1_AND_EXCLAMATION_POINT }
#define Key_2 (Key){ KEY_FLAGS, HID_KEYBOARD_2_AND_AT }
#define Key_3 (Key){ KEY_FLAGS, HID_KEYBOARD_3_AND_POUND }
#define Key_4 (Key){ KEY_FLAGS, HID_KEYBOARD_4_AND_DOLLAR }
#define Key_5 (Key){ KEY_FLAGS, HID_KEYBOARD_5_AND_PERCENT }
#define Key_6 (Key){ KEY_FLAGS, HID_KEYBOARD_6_AND_CARAT }
#define Key_7 (Key){ KEY_FLAGS, HID_KEYBOARD_7_AND_AMPERSAND }
#define Key_8 (Key){ KEY_FLAGS, HID_KEYBOARD_8_AND_ASTERISK }
#define Key_9 (Key){ KEY_FLAGS, HID_KEYBOARD_9_AND_LEFT_PAREN }
#define Key_0 (Key){ KEY_FLAGS, HID_KEYBOARD_0_AND_RIGHT_PAREN }
#define Key_A (Key){ KEY_FLAGS, HID_KEYBOARD_A_AND_A }
#define Key_B (Key){ KEY_FLAGS, HID_KEYBOARD_B_AND_B }
#define Key_C (Key){ KEY_FLAGS, HID_KEYBOARD_C_AND_C }
#define Key_D (Key){ KEY_FLAGS, HID_KEYBOARD_D_AND_D }
#define Key_E (Key){ KEY_FLAGS, HID_KEYBOARD_E_AND_E }
#define Key_F (Key){ KEY_FLAGS, HID_KEYBOARD_F_AND_F }
#define Key_G (Key){ KEY_FLAGS, HID_KEYBOARD_G_AND_G }
#define Key_H (Key){ KEY_FLAGS, HID_KEYBOARD_H_AND_H }
#define Key_I (Key){ KEY_FLAGS, HID_KEYBOARD_I_AND_I }
#define Key_J (Key){ KEY_FLAGS, HID_KEYBOARD_J_AND_J }
#define Key_K (Key){ KEY_FLAGS, HID_KEYBOARD_K_AND_K }
#define Key_L (Key){ KEY_FLAGS, HID_KEYBOARD_L_AND_L }
#define Key_M (Key){ KEY_FLAGS, HID_KEYBOARD_M_AND_M }
#define Key_N (Key){ KEY_FLAGS, HID_KEYBOARD_N_AND_N }
#define Key_O (Key){ KEY_FLAGS, HID_KEYBOARD_O_AND_O }
#define Key_P (Key){ KEY_FLAGS, HID_KEYBOARD_P_AND_P }
#define Key_Q (Key){ KEY_FLAGS, HID_KEYBOARD_Q_AND_Q }
#define Key_R (Key){ KEY_FLAGS, HID_KEYBOARD_R_AND_R }
#define Key_S (Key){ KEY_FLAGS, HID_KEYBOARD_S_AND_S }
#define Key_T (Key){ KEY_FLAGS, HID_KEYBOARD_T_AND_T }
#define Key_U (Key){ KEY_FLAGS, HID_KEYBOARD_U_AND_U }
#define Key_V (Key){ KEY_FLAGS, HID_KEYBOARD_V_AND_V }
#define Key_W (Key){ KEY_FLAGS, HID_KEYBOARD_W_AND_W }
#define Key_X (Key){ KEY_FLAGS, HID_KEYBOARD_X_AND_X }
#define Key_Y (Key){ KEY_FLAGS, HID_KEYBOARD_Y_AND_Y }
#define Key_Z (Key){ KEY_FLAGS, HID_KEYBOARD_Z_AND_Z }

#define Key_Backtick (Key){ KEY_FLAGS, HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE }
#define Key_Minus (Key){ KEY_FLAGS, HID_KEYBOARD_MINUS_AND_UNDERSCORE }
#define Key_Equals (Key){ KEY_FLAGS, HID_KEYBOARD_EQUALS_AND_PLUS }
#define Key_LBracket (Key){ KEY_FLAGS, HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE }
#define Key_RBracket (Key){ KEY_FLAGS, HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE }
#define Key_Backslash (Key){ KEY_FLAGS, HID_KEYBOARD_BACKSLASH_AND_PIPE }
#define Key_Pipe LSHIFT(Key_Backslash)
#define Key_LSquareBracket (Key){ KEY_FLAGS, HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE }
#define Key_RSquareBracket (Key){ KEY_FLAGS, HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE }
#define Key_LCurlyBracket LSHIFT(Key_LSquareBracket)
#define Key_RCurlyBracket LSHIFT(Key_RSquareBracket)
#define Key_Semicolon (Key){ KEY_FLAGS, HID_KEYBOARD_SEMICOLON_AND_COLON }
#define Key_Quote (Key){ KEY_FLAGS, HID_KEYBOARD_QUOTE_AND_DOUBLEQUOTE }
#define Key_Comma (Key){ KEY_FLAGS, HID_KEYBOARD_COMMA_AND_LESS_THAN }
#define Key_Period (Key){ KEY_FLAGS, HID_KEYBOARD_PERIOD_AND_GREATER_THAN }
#define Key_Space (Key){ KEY_FLAGS, HID_KEYBOARD_SPACEBAR}
#define Key_Slash (Key){ KEY_FLAGS, HID_KEYBOARD_SLASH_AND_QUESTION_MARK }

#define Key_LEFT_PAREN LSHIFT(Key_9)
#define Key_RIGHT_PAREN LSHIFT(Key_0)


#define Key_KeypadClear (Key){ KEY_FLAGS, HID_KEYPAD_CLEAR }
#define Key_KeypadSlash (Key){ KEY_FLAGS, HID_KEYPAD_DIVIDE }
#define Key_KeypadMultiply (Key){ KEY_FLAGS, HID_KEYPAD_MULTIPLY }
#define Key_KeypadMinus (Key){ KEY_FLAGS, HID_KEYPAD_SUBTRACT }
#define Key_KeypadPlus (Key){ KEY_FLAGS, HID_KEYPAD_ADD }
#define Key_Enter (Key){ KEY_FLAGS, HID_KEYBOARD_ENTER }
#define Key_Keypad1 (Key){ KEY_FLAGS, HID_KEYPAD_1_AND_END }
#define Key_Keypad2 (Key){ KEY_FLAGS, HID_KEYPAD_2_AND_DOWN_ARROW}
#define Key_Keypad3 (Key){ KEY_FLAGS, HID_KEYPAD_3_AND_PAGE_DOWN}
#define Key_Keypad4 (Key){ KEY_FLAGS, HID_KEYPAD_4_AND_LEFT_ARROW }
#define Key_Keypad5 (Key){ KEY_FLAGS, HID_KEYPAD_5 }
#define Key_Keypad6 (Key){ KEY_FLAGS, HID_KEYPAD_6_AND_RIGHT_ARROW }
#define Key_Keypad7 (Key){ KEY_FLAGS, HID_KEYPAD_7_AND_HOME }
#define Key_Keypad8 (Key){ KEY_FLAGS, HID_KEYPAD_8_AND_UP_ARROW }
#define Key_Keypad9 (Key){ KEY_FLAGS, HID_KEYPAD_9_AND_PAGE_UP }
#define Key_Keypad0 (Key){ KEY_FLAGS, HID_KEYPAD_0_AND_INSERT }
#define Key_KeypadDot (Key){ KEY_FLAGS, HID_KEYPAD_PERIOD_AND_DELETE }
#define Key_PcApplciation (Key){ KEY_FLAGS, HID_KEYBOARD_APPLICATION }
#define Key_Help (Key){ KEY_FLAGS, HID_KEYBOARD_HELP }
#define KEY_BACKLIGHT_DOWN 0xF1
#define KEY_BACKLIGHT_UP 0xF2
#define Key_BacklightDn (Key){ KEY_FLAGS, KEY_BACKLIGHT_DOWN }
#define Key_BacklightUp (Key){ KEY_FLAGS, KEY_BACKLIGHT_UP }
#define KEY_RIGHT_FN2 0xfe
#define Key_RFN2 (Key){ KEY_FLAGS, KEY_RIGHT_FN2 }
#define KEY_LEFT_FN2 0xff
#define Key_LFN2 (Key){ KEY_FLAGS, KEY_LEFT_FN2 }

#define Key_Undo (Key){ KEY_FLAGS, HID_KEYBOARD_UNDO }
#define Key_Cut (Key){ KEY_FLAGS, HID_KEYBOARD_CUT }
#define Key_Copy (Key){ KEY_FLAGS, HID_KEYBOARD_COPY }
#define Key_Paste (Key){ KEY_FLAGS, HID_KEYBOARD_PASTE }


#define Key_Keymap0 (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP , KEYMAP_0 }
#define Key_Keymap1 (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP , KEYMAP_1 }
#define Key_Keymap2 (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP , KEYMAP_2 }
#define Key_Keymap3 (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP , KEYMAP_3 }
#define Key_Keymap4 (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP , KEYMAP_4 }
#define Key_Keymap5 (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP , KEYMAP_5 }
#define Key_Keymap0_Momentary (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_0 + MOMENTARY_OFFSET}
#define Key_Keymap1_Momentary (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_1 + MOMENTARY_OFFSET}
#define Key_Keymap2_Momentary (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_2 + MOMENTARY_OFFSET }
#define Key_Keymap3_Momentary (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_3 + MOMENTARY_OFFSET }
#define Key_Keymap4_Momentary (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_4 + MOMENTARY_OFFSET }
#define Key_Keymap5_Momentary (Key){ KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_5 + MOMENTARY_OFFSET }

#define Key_KeymapNext_Momentary (Key) {KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_NEXT + MOMENTARY_OFFSET }
#define Key_KeymapPrevious_Momentary (Key) {KEY_FLAGS | SYNTHETIC | SWITCH_TO_KEYMAP, KEYMAP_PREVIOUS + MOMENTARY_OFFSET }




#define Key_LEDEffectNext (Key) { KEY_FLAGS | SYNTHETIC | IS_INTERNAL | LED_TOGGLE, 0 }
