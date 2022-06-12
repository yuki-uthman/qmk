#include QMK_KEYBOARD_H

#include "print.h"
#include "features/casemodes.h"
#include "features/custom_shift_keys.h"
#include "features/abbreviation.h"
#include "features/vim.h"
#include "features/left_ctrl.h"
#include "features/macOS.h"

#define ___ KC_TRNS // just for easy reading
#define XXX KC_NO    // just for easy reading

#define TMUX_KEY C(KC_Z)
#define LEFT_THUMB  LT(0, KC_1)

const custom_shift_key_t custom_shift_keys[] = {
  {KC_M, KC_ENT},       // Ctrl + M => Enter
  {KC_H, KC_BSPC},      // Ctrl + H => Backspace
  {KC_J, KC_DOWN},
  {KC_K, KC_UP},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

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
    MAC,
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

// Tap Dance declarations
enum {
    CAPSWORD, SYMLOCK,
};

void capsword(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
        case 2:
            enable_caps_word();
            break;
    }
}

void symlock(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            set_oneshot_layer(_SYMBOL, ONESHOT_START);
            break;
        case 2:
            layer_invert(_SYMBOL);
            break;
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [CAPSWORD] = ACTION_TAP_DANCE_FN(capsword),
    [SYMLOCK] = ACTION_TAP_DANCE_FN(symlock),
};


#define SFT_UNDERSCORE  LSFT_T(KC_UNDERSCORE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
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
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_VIM,
  MAC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS,
  KC_ESC,   KC_A,   KC_S,     KC_D,   KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  SFT_UNDERSCORE,  KC_Z,  KC_X,    KC_C,  KC_V,  KC_B, KC_MUTE,     XXX, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
    KC_LGUI, MO(_TMUX), MT(MOD_LCTL, KC_ENT), LEFT_THUMB, OSL(_SYMBOL),      TD(CAPSWORD),  MT(MOD_RCTL, KC_SPC), MO(_SYMBOL), KC_RALT, KC_RGUI
),



[_VIM] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_QWERTY,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS,
  KC_ESC,   KC_A,   KC_S,     KC_D,   KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  SFT_UNDERSCORE,  KC_Z,  KC_X,    KC_C,  KC_V,  KC_B, KC_MUTE,     XXX, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
    KC_LGUI,KC_LALT,MO(_TMUX), MT(MOD_LCTL, KC_ENT), TD(CAPSWORD),      TD(CAPSWORD),  MT(MOD_RCTL, KC_SPC), MO(_SYMBOL), KC_RALT, KC_RGUI
),









/*
 * TMUX
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_TMUX] = LAYOUT(
  ___,   ___,   ___,    ___,    ___,    ___,                ___,    ___,    ___,    ___,    ___,  ___,
  ___,   ___,   ___,    ___,    ___,    ___,                ___,    ___,    ___,    ___, ___,  WINDOW_HSPLIT,
  ___,   ___,   ___,    ___,    ___,    ___,                WINDOW_PREV,  SESSION_NEXT,  SESSION_PREV,  WINDOW_NEXT,  WINDOW_ALT,  ___,
  ___,   ___,   ___,    PANE_CLOSE, ___, ___, ___,     ___, ___,    ___,    ___,  ___, WINDOW_VSPLIT,  ___,
                        ___,___,___,___, ___,               ___,  WINDOW_ZOOM, ___, ___, ___
),













/* SYMBOL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   '  |   <  |   >  |   "  |   .  |                    |   &  |      |   [  |   ]  |   %  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   -  |   +  |   =  |   #  |-------.    ,-------|   |  |   :  |   (  |   )  |   ?  |   '  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|   ^  |  /   |  *   |   \  |      |-------|    |-------|   n  |   $  |   {  |   }  |   @  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_SYMBOL] = LAYOUT(
___,   ___,   ___,    ___,    ___,    ___,                      ___,    ___,    ___,    ___,    ___,  ___,
___,   KC_QUOT, KC_LABK,  KC_RABK,  KC_DQUO,  ___,           KC_AMPR,    ___,    KC_LBRC,  KC_RBRC,  KC_PERC,  ___,
___,   KC_EXLM, KC_MINS,  KC_PLUS,  KC_EQL,   KC_HASH,          KC_PIPE,  KC_COLN,  KC_LPRN,  KC_RPRN,  KC_AT,  ___,
___,   KC_CIRC, KC_SLSH,  KC_ASTR,  KC_BSLS,  ___,  ___,   ___, ___,      KC_DLR,   KC_LCBR,  KC_RCBR,  KC_QUES,  ___,
                        ___,___,___,___, ___,               ___,  ___, ___, ___, ___
),

};

void matrix_scan_user(void) {
    clear_recent_keys();  // Timed out; clear the buffer.
}

// Returns true if the case modes should terminate, false if they continue
// Note that the keycodes given to this function will be stripped down to
// basic keycodes if they are dual function keys. Meaning a modtap on 'a'
// will pass KC_A rather than LSFT_T(KC_A).
// Case delimiters will also not be passed into this function.
bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                return true;
            }
            break;
        default:
            if (record->event.pressed) {
                return true;
            }
            break;
    }
    return false;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_case_modes(keycode, record))           { return false; }
    if (!process_custom_shift_keys(keycode, record))    { return false; }
    if (!process_abbreviation(keycode, record))         { return false; }
    if (!process_vim_mode(keycode, record))             { return false; }
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
        case CAPSWORD:
            if (record->event.pressed) {
                enable_caps_word();
            }
            return false;
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_VIM:
            if (record->event.pressed) {
                toggle_vim_mode();
            }
            return false;
        case LEFT_THUMB:
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    xprintf("left thumb tap pressed\n");
                } else {
                    xprintf("left thumb tap released\n");
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    enable_left_ctrl();
                    xprintf("left thumb hold pressed\n");
                } else {
                    disable_left_ctrl();
                    xprintf("left thumb hold released\n");
                }
            }
            return false;  // Skip default handling.
        case MAC:
            if (record->tap.count > 0) {    // Key is being tapped.
                if (record->event.pressed) {
                    xprintf("mac layer tap pressed\n");
                } else {
                    xprintf("mac layer tap released\n");
                }
            } else {                        // Key is being held.
                if (record->event.pressed) {
                    enable_mac_layer();
                    xprintf("mac layer hold pressed\n");
                } else {
                    disable_mac_layer();
                    xprintf("mac layer hold released\n");
                }
            }
            return false;  // Skip default handling.
    }
    return true;
}

