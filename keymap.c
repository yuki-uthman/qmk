#include QMK_KEYBOARD_H

#include "print.h"
#include "features/caps_word.h"
#include "features/left_ctrl.h"
#include "features/right_ctrl.h"
#include "features/tmux.h"

#define ___ KC_TRNS // just for easy reading
#define XXX KC_NO    // just for easy reading

#define LEFT_THUMB      LT(0, KC_1)
#define RIGHT_THUMB     LT(0, KC_2)
#define TMUX            LT(0, KC_3)
#define CAPSWORD        LT(0, KC_4)
#define CUSTOM_C        LT(0, KC_5) // 16418
#define CUSTOM_V        LT(0, KC_6) // 16419

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _SYMBOL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   ?  |   !  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  XXX,      KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      XXX,
  KC_GRV,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSLS,
  KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT,
  ___,  KC_Z,  KC_X,    CUSTOM_C,  CUSTOM_V,  KC_B, KC_MUTE,        XXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUES,   KC_EXLM,
    TMUX, KC_LALT, CAPSWORD, LEFT_THUMB, OSL(_SYMBOL),       OSL(_SYMBOL),  RIGHT_THUMB, CAPSWORD, KC_RALT, TMUX
),

/* SYMBOL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |   [  |   &  |   #  |   ]  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   ^  |   +  |   ?  |  $   |                    |   {  |   "  |   =  |   }  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   <  |   *  |   +  |  >   |-------.    ,-------|   (  |   :  |   -  |   )  |      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |   _  |   ~  |   /  |  *   |-------|    |-------|   <  |   /  |   _  |   >  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_SYMBOL] = LAYOUT(
___,   ___, ___,    ___,  ___,   ___,                       KC_LBRC,  KC_AMPR,   KC_HASH, KC_RBRC,  ___,  ___,
___,   ___, KC_CIRC,  KC_PLUS,  KC_QUES,  KC_DLR,           KC_LCBR,  KC_DQUO,   KC_EQL,  KC_RCBR,  ___,  ___,
___,   ___, KC_LABK,  KC_ASTR,  KC_PLUS,  KC_RABK,          KC_LPRN,  KC_COLN,   KC_MINS, KC_RPRN,  ___,  ___,
___,   ___, KC_UNDS,  KC_TILD,  KC_SLSH,  KC_ASTR, ___,___, KC_LABK,  KC_SLSH,   KC_UNDS, KC_RABK,  ___,  ___,
                        ___,___,___, ___, ___,               ___,   ___, ___, ___, ___
),

};


bool caps_word_press_user(uint16_t keycode) {

    xprintf("%u pressed\n", keycode);

    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case 34:
        case 35:
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_caps_word(keycode, record))            { return false; }
    if (!process_right_ctrl(keycode, record))           { return false; }
    if (!process_left_ctrl(keycode, record))            { return false; }
    if (!process_tmux(keycode, record))                 { return false; }

    switch (keycode) {
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

        case TMUX:
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    register_code16(TMUX_KEY);
                } else {
                    unregister_code16(TMUX_KEY);
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    enable_tmux();
                } else {
                    disable_tmux();
                }
            }
            return false;  // Skip default handling.

        default:
            return true;  // Process all other keycodes normally.
    }
}

