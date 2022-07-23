#include "right_ctrl.h"

#include "print.h"


static bool right_ctrl_enabled = false;

bool right_ctrl_is_enabled(void) {
    return right_ctrl_enabled;
}
void enable_right_ctrl(void) {
    right_ctrl_enabled = true;
}
void disable_right_ctrl(void) {
    right_ctrl_enabled = false;
}
void toggle_right_ctrl(void) {
    if (right_ctrl_enabled) {
        disable_right_ctrl();
    }
    else {
        enable_right_ctrl();
    }
}

/* return false to finish processing of the key */
/* return true to fall through to the qmk processing of the key */

bool process_right_ctrl(uint16_t keycode, const keyrecord_t *record) {

    if (!right_ctrl_is_enabled()) { return true; }
    /* xprintf("%u pressed\n", keycode); */

    switch (keycode) {

    // {}
    case KC_O:
        if (record->event.pressed) {
            register_code16(KC_RCBR);
        } else {
            unregister_code16(KC_RCBR);
        }
        return false;
    case KC_I:
        if (record->event.pressed) {
            register_code16(KC_LCBR);
        } else {
            unregister_code16(KC_LCBR);
        }
        return false;

    // ()
    case KC_L:
        if (record->event.pressed) {
            register_code16(KC_RPRN);
        } else {
            unregister_code16(KC_RPRN);
        }
        return false;
    case KC_K:
        if (record->event.pressed) {
            register_code16(KC_LPRN);
        } else {
            unregister_code16(KC_LPRN);
        }
        return false;

    // []
    case KC_DOT:
        if (record->event.pressed) {
            register_code16(KC_RBRC);
        } else {
            unregister_code16(KC_RBRC);
        }
        return false;
    case KC_COMM:
        if (record->event.pressed) {
            register_code16(KC_LBRC);
        } else {
            unregister_code16(KC_LBRC);
        }
        return false;

    case 16414: // handle left_thumb
        if (record->event.pressed) {
            register_code16(G(KC_SPC)); // open Alfred
        } else {
            unregister_code16(G(KC_SPC));
        }
        return false;
    default: // everything else Ctrl + Keycode
        if (record->event.pressed) {
            register_code16(C(keycode));
        } else {
            if (keycode == 16415) { // handle the hold without pressing any other key and release
                return true;
            }
            unregister_code16(C(keycode));
        }
        return false;
    }
}
