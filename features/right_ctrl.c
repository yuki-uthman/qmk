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

    case KC_K:
        if (record->event.pressed) {
            tap_code16(S(KC_Z));
            tap_code16(S(KC_Z));
        }
        return false;

    // custom keys
    case 16416: // MAC
        if (record->event.pressed) {
            register_code16(KC_BSPC);
        } else {
            unregister_code16(KC_BSPC);
        }
        return false;
    case 16418: // CUSTOM_C
        if (record->event.pressed) {
            register_code16(C(KC_C));
        } else {
            unregister_code16(C(KC_C));
        }
        return false;
    case 16419: // CUSTOM_V
        if (record->event.pressed) {
            register_code16(C(KC_V));
        } else {
            unregister_code16(C(KC_V));
        }
        return false;
    case 16414: // handle the left thumb
        if (record->event.pressed) {
            register_code16(C(KC_SPC));
        } else {
            unregister_code16(C(KC_SPC));
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
