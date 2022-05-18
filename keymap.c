#include QMK_KEYBOARD_H

#include "features/casemodes.h"
#include "features/custom_shift_keys.h"
#include "features/abbreviation.h"

#define ___ KC_TRNS // just for easy reading
#define XXX KC_NO    // just for easy reading

#define TMUX_KEY "z"

const custom_shift_key_t custom_shift_keys[] = {
  {KC_M, KC_ENT},       // Ctrl + M => Enter
  {KC_H, KC_BSPC},      // Ctrl + H => Backspace
  {KC_MINS, KC_EQL }, // Shift - is =
  {KC_COLN, KC_SCLN}, // Shift : is ;
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _TMUX,
    _SYMBOL,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_TMUX,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    ARROW,
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
    CAPSWORD,
    SNAKECASE,
};

// Tap Dance declarations
enum {
    TD_DOT_NEXTSEN,
};

void abbreviation(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code(KC_DOT);
    unregister_code(KC_DOT);
    break;
  case 2:
    SEND_STRING(". ");
    add_oneshot_mods(MOD_BIT(KC_LSFT));
    break;
  }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    /* [TD_DOT_NEXTSEN] = ACTION_TAP_DANCE_FN(next_sentence), */
};

// Home row mods for QWERTY layer.
// left hand
#define QHOME_F LCTL_T(KC_F)
#define QHOME_D LSFT_T(KC_D)
#define QHOME_S LT(_SYMBOL, KC_S)
#define QHOME_A LGUI_T(KC_A)
#define QHOME_Z LALT_T(KC_Z)

// right hand
#define QHOME_J RCTL_T(KC_J)
#define QHOME_K RSFT_T(KC_K)
#define QHOME_L LT(_SYMBOL, KC_L)
#define QHOME_SC RGUI_T(KC_SCLN)
#define QHOME_SL LALT_T(KC_SLSH)

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
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS,
  KC_CAPS,  QHOME_A,QHOME_S, QHOME_D, QHOME_F, KC_G,                     KC_H,    QHOME_J, QHOME_K, QHOME_L, QHOME_SC,  KC_QUOT,
  SFT_UNDERSCORE,  QHOME_Z,  KC_X,    KC_C,  KC_V,  KC_B, KC_MUTE,     XXX,KC_N,    KC_M, KC_COMM,  KC_DOT, QHOME_SL, KC_RSFT,
    KC_LGUI,KC_LALT,MO(_TMUX), MT(MOD_LCTL, KC_ENT), SNAKECASE,      CAPSWORD,  MT(MOD_RCTL, KC_SPC), MO(_SYMBOL), KC_RALT, KC_RGUI
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
  ___,   ___,   ___,    ___,    ___,    ___,                ___,    ___,    ___,    ___, ___,  WINDOW_VSPLIT,
  ___,   ___,   ___,    ___,    ___,    ___,                WINDOW_PREV,  SESSION_NEXT,  SESSION_PREV,  WINDOW_NEXT,  WINDOW_ALT,  ___,
  ___,   ___,   ___,    PANE_CLOSE, ___, ___, ___,     ___, ___,    ___,    ___,  ___, WINDOW_HSPLIT,  ___,
                        ___,___,___,___, ___,               ___,  WINDOW_ZOOM, ___, ___, ___
),



[_SYMBOL] = LAYOUT(
___,   ___,   ___,    ___,    ___,    ___,                      ___,    ___,    ___,    ___,    ___,  ___,
___,   KC_QUOT, KC_LABK,  KC_RABK,  KC_DQUO,  KC_DOT,           KC_AMPR,    ___,    KC_LBRC,  KC_RBRC,  KC_PERC,  ___,
___,   KC_EXLM, KC_MINS,  KC_PLUS,  KC_EQL,   KC_HASH,          KC_PIPE,  KC_COLN,  KC_LPRN,  KC_RPRN,  KC_QUES,  ___,
___,   KC_CIRC, KC_SLSH,  KC_ASTR,  KC_BSLS,  ___,  ___,   ___, ___,      KC_DLR,   KC_LCBR,  KC_RCBR,  KC_AT,  ___,
                        ___,___,___,___, ___,               ___,  ___, ___, ___, ___
),









/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
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

    if (!process_case_modes(keycode, record)) { return false; }
    if (!process_custom_shift_keys(keycode, record)) { return false; }
    if (!process_abbreviation(keycode, record)) { return false; }

    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    switch (keycode) {
        case PANE_CLOSE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)"x");
            }
            break;
        case WINDOW_NEXT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)"n");
            }
            break;
        case WINDOW_PREV:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)"p");
            }
            break;
        case WINDOW_ALT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)"l");
            }
            break;
        case WINDOW_ZOOM:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)"z");
            }
            break;
        case WINDOW_HSPLIT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)SS_LSFT("5"));
            }
            break;
        case WINDOW_VSPLIT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)SS_LSFT("'"));
            }
            break;
        case SESSION_NEXT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)SS_LSFT("0"));
            }
            break;
        case SESSION_PREV:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(TMUX_KEY)SS_LSFT("9"));
            }
            break;
        case ARROW:  // Arrow macro, types -> or =>.
            if (record->event.pressed) {
              if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
                del_mods(MOD_MASK_SHIFT);  // Temporarily delete shift.
                del_oneshot_mods(MOD_MASK_SHIFT);
                SEND_STRING("=>");
                set_mods(mods);            // Restore mods.
              } else {
                SEND_STRING("->");
              }
            }
            return false;
        case SFT_UNDERSCORE:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_UNDERSCORE);
                return false;        // Return false to ignore further processing of key
            }
            break;
        case CAPSWORD:
            if (record->event.pressed) {
                enable_caps_word();
            }
            return false;
        case SNAKECASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_UNDS);
            }
            return false;
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
    }
    return true;
}

