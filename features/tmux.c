#include "tmux.h"

#include "print.h"


static bool tmux_enabled = false;

bool tmux_is_enabled(void) {
    return tmux_enabled;
}
void enable_tmux(void) {
    tmux_enabled = true;
}
void disable_tmux(void) {
    tmux_enabled = false;
}

/* return false to finish processing of the key */
/* return true to fall through to the qmk processing of the key */

bool process_tmux(uint16_t keycode, const keyrecord_t *record) {

    if (!tmux_is_enabled()) { return true; }

    switch (keycode) {

        case KC_L:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_N);
            }
            break;
        case KC_H:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_P);
            }
            break;
        case KC_J:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_0));
            }
            break;
        case KC_K:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_9));
            }
            break;

        case 16418: // custom_c
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_X);
            }
            break;
        case 16419: // custom_v
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_5));
            }
            break;
        case KC_COMM:
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(S(KC_QUOT));
            }
            break;

        case 16415: // handle right thumb
            if (record->event.pressed) {
                tap_code16(TMUX_KEY);
                tap_code16(KC_Z);
            }
            break;

        default: // dont do anything for other keys
            return true;
    }

    // cancel further processing of the key
    return false;
}
