#include QMK_KEYBOARD_H

#include "print.h"
#include "features/caps_word.h"
#include "features/left_ctrl.h"
#include "features/right_ctrl.h"
#include "features/macOS.h"

#define ___ KC_TRNS // just for easy reading
#define XXX KC_NO    // just for easy reading

#define TMUX_KEY C(KC_Z)

#define LEFT_THUMB      LT(0, KC_1)
#define RIGHT_THUMB     LT(0, KC_2)
#define MAC             LT(0, KC_3)
#define CAPSWORD        LT(0, KC_4)
#define CUSTOM_C        LT(0, KC_5) // 16418
#define CUSTOM_V        LT(0, KC_6) // 16419

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _VIM,
    _TMUX,
    _SYMBOL,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_VIM,
    KC_TMUX,
    NEXTSEN,
    SESSION_NEXT,
    SESSION_PREV,
    WINDOW_NEXT,
    WINDOW_PREV,
    WINDOW_ALT,
    WINDOW_ZOOM,
    WINDOW_VSPLIT,
    WINDOW_HSPLIT,
    PANE_CLOSE,
};


#define SFT_UNDERSCORE  LSFT_T(KC_UNDERSCORE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSLS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  MAC,   KC_A,   KC_S,     KC_D,   KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  ___,  KC_Z,  KC_X,    CUSTOM_C,  CUSTOM_V,  KC_B, KC_MUTE,     XXX, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
    MO(_TMUX), KC_LALT, ___, LEFT_THUMB, CAPSWORD,       OSL(_SYMBOL),  RIGHT_THUMB, ___, KC_RALT, KC_RGUI
),


[_TMUX] = LAYOUT(
  ___,   ___,   ___,    ___,    ___,    ___,                ___,    ___,    ___,    ___,    ___,  ___,
  ___,   ___,   ___,    ___,    ___,    ___,                ___,    ___,    ___,    ___, ___,  WINDOW_HSPLIT,
  ___,   ___,   ___,    ___,    ___,    ___,                WINDOW_PREV,  SESSION_NEXT,  SESSION_PREV,  WINDOW_NEXT,  WINDOW_ALT,  ___,
  ___,   ___,   ___,    PANE_CLOSE, ___, ___, ___,     ___, ___,    ___,    ___,  ___, WINDOW_VSPLIT,  ___,
                        ___,___,___,___, ___,               ___,  WINDOW_ZOOM, ___, ___, ___
),


/* SYMBOL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   <  |   >  |   `  |   @  |                    |   &  |   $  |   {  |   }  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   -  |   +  |   =  |   #  |-------.    ,-------|   |  |   ?  |   (  |   )  |   :  |   "  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|   ^  |   /  |   *  |   \  |   %  |-------|    |-------|   ~  |   _  |   [  |   ]  |   ?  |   _  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_SYMBOL] = LAYOUT(
___,   KC_EXLM, KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,              KC_CIRC, KC_AMPR,  KC_LBRC,  KC_RBRC,  ___,  ___,
___,   ___, KC_LABK,  KC_RABK,  KC_GRV,   KC_AT,                KC_AMPR, KC_DLR,   KC_LCBR,  KC_RCBR,  ___,  ___,
___,   KC_EXLM, KC_MINS,  KC_PLUS,  KC_EQL,   KC_HASH,              KC_PIPE, KC_QUES,  KC_LPRN,  KC_RPRN,  KC_COLN,  KC_DQUO,
___,   KC_CIRC, KC_SLSH,  KC_ASTR,  KC_BSLS,  KC_PERC,  ___,   ___, KC_TILD, KC_UNDS,  KC_LBRC,  KC_RBRC,  KC_QUES,  KC_UNDS,
                        ___,___,___,___, ___,               ___,  ___, ___, ___, ___
),

};

void oneshot_mods_changed_user(uint8_t mods) {
  bool shifted = (mods & MOD_MASK_SHIFT) != 0;
  xprintf("%u\n", shifted ? "[ON]": "[OFF]");

}

bool caps_word_press_user(uint16_t keycode) {

    xprintf("%u pressed\n", keycode);

    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
          add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
          return true;

        // Keycodes that continue Caps Word, without shifting.
        /* case KC_1 ... KC_0: */
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
          return true;

        case 31: // LEFT_THUMB space
          return false;

        default:
          return false;  // Deactivate Caps Word.
    }
}

/* void matrix_scan_user(void) { */
/*     clear_recent_keys();  // Timed out; clear the buffer. */
/* } */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_caps_word(keycode, record))            { return false; }
    if (!process_right_ctrl(keycode, record))           { return false; }
    if (!process_left_ctrl(keycode, record))            { return false; }
    if (!process_mac_layer(keycode, record))            { return false; }

    switch (keycode) {
        case PANE_CLOSE:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_X);
            }
            break;
        case WINDOW_NEXT:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_N);
            }
            break;
        case WINDOW_PREV:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_P);
            }
            break;
        case WINDOW_ALT:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_L);
            }
            break;
        case WINDOW_ZOOM:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_Z);
            }
            break;
        case WINDOW_HSPLIT:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_5));
            }
            break;
        case WINDOW_VSPLIT:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_QUOT));
            }
            break;
        case SESSION_NEXT:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_0));
            }
            break;
        case SESSION_PREV:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_9));
            }
            break;
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

        case CUSTOM_C:  // Comma on tap, Ctrl+C on long press.
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    register_code16(KC_C);
                } else {
                    unregister_code16(KC_C);
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    register_code16(G(KC_C));
                } else {
                    unregister_code16(G(KC_C));
                }
            }
            return false;  // Skip default handling.

        case CUSTOM_V:  // Dot on tap, Ctrl+V on long press.
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    register_code16(KC_V);
                } else {
                    unregister_code16(KC_V);
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    register_code16(G(KC_V));
                } else {
                    unregister_code16(G(KC_V));
                }
            }
            return false;  // Skip default handling.

        case CAPSWORD:
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    set_oneshot_mods(MOD_BIT(KC_LSFT));
                } else {
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    caps_word_on();
                } else {
                }
            }
            return false;  // Skip default handling.
                           //
        case LEFT_THUMB:
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                } else {
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    enable_left_ctrl();
                } else {
                    disable_left_ctrl();
                }
            }
            return false;  // Skip default handling.
        case RIGHT_THUMB:
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    register_code16(KC_SPC);
                } else {
                    unregister_code16(KC_SPC);
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    enable_right_ctrl();
                } else {
                    disable_right_ctrl();
                }
            }
            return false;  // Skip default handling.
        case MAC:
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    register_code16(KC_ESC);
                } else {
                    unregister_code16(KC_ESC);
                }
                caps_word_off();
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    enable_mac_layer();
                } else {
                    disable_mac_layer();
                }
            }
            return false;  // Skip default handling.

    }
    return true;
}

