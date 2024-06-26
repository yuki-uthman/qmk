#include "left_ctrl.h"

#include "print.h"


static bool left_ctrl_enabled = false;

bool left_ctrl_is_enabled(void) {
    return left_ctrl_enabled;
}
void enable_left_ctrl(void) {
    left_ctrl_enabled = true;
}
void disable_left_ctrl(void) {
    left_ctrl_enabled = false;
}
void toggle_left_ctrl(void) {
    if (left_ctrl_enabled) {
        disable_left_ctrl();
    }
    else {
        enable_left_ctrl();
    }
}

/* return false to finish processing of the key */
/* return true to fall through to the qmk processing of the key */

bool process_left_ctrl(uint16_t keycode, const keyrecord_t *record) {

    if (!left_ctrl_is_enabled()) { return true; }

    static bool g_is_held = false;
    if (record->event.pressed) {
        if (g_is_held) {
            tap_code16(S(keycode));
            return false;
        }
    }

    switch (keycode) {

    case KC_G:
        g_is_held = record->event.pressed;
        return false;

    case KC_H:
        if (record->event.pressed) {
            register_code16(KC_LEFT);
        } else {
            unregister_code16(KC_LEFT);
        }
        return false;
    case KC_J:
        if (record->event.pressed) {
            register_code16(KC_DOWN);
        } else {
            unregister_code16(KC_DOWN);
        }
        return false;
    case KC_K:
        if (record->event.pressed) {
            register_code16(KC_UP);
        } else {
            unregister_code16(KC_UP);
        }
        return false;
    case KC_L:
        if (record->event.pressed) {
            register_code16(KC_RIGHT);
        } else {
            unregister_code16(KC_RIGHT);
        }
        return false;
    case KC_M:
        if (record->event.pressed) {
            register_code16(KC_ENT);
        } else {
            unregister_code16(KC_ENT);
        }
        return false;

    case KC_Q:
        if (record->event.pressed) {
            SEND_STRING(":q!");
        }
        return false;

    case KC_BSPC:
        if (record->event.pressed) {
            register_code16(C(KC_W));
        } else {
            unregister_code16(C(KC_W));
        }
        return false;


    case 16415: // handle right_thumb
        if (record->event.pressed) {
            register_code16(G(KC_SPC)); // open Alfred
        } else {
            unregister_code16(G(KC_SPC));
        }
        return false;

    default: // everything else Ctrl + Keycode
        if (record->event.pressed) {
            /* xprintf("%u pressed\n", keycode); */
            register_code16(C(keycode));
        } else {
            if (keycode == 16414) { // handle the hold without pressing any other key and release
                return true;
            }
            /* xprintf("%u released\n", keycode); */
            unregister_code16(C(keycode));
        }
        return false;
    }
}
