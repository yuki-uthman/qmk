#include "left_ctrl.h"

#include "print.h"


static bool left_ctrl_enabled = false;

// Check to see if vim mode is enabled
bool left_ctrl_is_enabled(void) {
    return left_ctrl_enabled;
}
// Enable vim mode
void enable_left_ctrl(void) {
    left_ctrl_enabled = true;
}
// Disable vim mode
void disable_left_ctrl(void) {
    left_ctrl_enabled = false;
}
// Toggle vim mode
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

    switch (keycode) {
    case KC_H:
        if (record->event.pressed) {
            register_code16(KC_BSPC);
        } else {
            unregister_code16(KC_BSPC);
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
    case KC_M:
        if (record->event.pressed) {
            register_code16(KC_ENT);
        } else {
            unregister_code16(KC_ENT);
        }
        return false;
    case 28972:
        if (record->event.pressed) {
            xprintf("space pressed\n");
            register_code16(G(KC_SPC));
        } else {
            unregister_code16(G(KC_SPC));
        }
        return false;
    default:
        if (record->event.pressed) {
            xprintf("%u pressed\n", keycode);
            register_code16(C(keycode));
        } else {
            if (keycode == 16414) { // handle the hold without pressing any other key and release
                return true;
            }
            xprintf("%u released\n", keycode);
            unregister_code16(C(keycode));
        }
        return false;
    }
}
