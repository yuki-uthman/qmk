#include "macOS.h"

#include "print.h"


static bool mac_layer_enabled = false;

// Check to see if vim mode is enabled
bool mac_layer_is_enabled(void) {
    return mac_layer_enabled;
}
// Enable vim mode
void enable_mac_layer(void) {
    mac_layer_enabled = true;
}
// Disable vim mode
void disable_mac_layer(void) {
    mac_layer_enabled = false;
    if (get_mods() & MOD_BIT(KC_LGUI)) {
        xprintf("get_mods = %u\n", get_mods());
        unregister_code16(KC_LGUI);
    }
}
// Toggle vim mode
void toggle_mac_layer(void) {
    if (mac_layer_enabled) {
        disable_mac_layer();
    }
    else {
        enable_mac_layer();
    }
}

/* return false to finish processing of the key */
/* return true to fall through to the qmk processing of the key */

bool process_mac_layer(uint16_t keycode, const keyrecord_t *record) {

    if (!mac_layer_is_enabled()) { return true; }

    switch (keycode) {
    case KC_H:
        if (record->event.pressed) {
            register_code16(LAG(KC_LEFT));
        } else {
            unregister_code16(LAG(KC_LEFT));
        }
        return false;
    case KC_L:
        if (record->event.pressed) {
            register_code16(LAG(KC_RIGHT));
        } else {
            unregister_code16(LAG(KC_RIGHT));
        }
        return false;
    case KC_J:
        if (record->event.pressed) {
            register_code16(KC_LGUI);
            register_code16(KC_TAB);
        } else {
            unregister_code16(KC_TAB);
        }
        return false;
    case KC_K:
        if (record->event.pressed) {
            register_code16(KC_LGUI);
            register_code16(KC_LSHIFT);
            register_code16(KC_TAB);
        } else {
            unregister_code16(KC_LSHIFT);
            unregister_code16(KC_TAB);
        }
        return false;
    case KC_N:
        if (record->event.pressed) {
            register_code16(LAG(KC_RIGHT));
        } else {
            unregister_code16(LAG(KC_RIGHT));
        }
        return false;
    case KC_P:
        if (record->event.pressed) {
            register_code16(LAG(KC_LEFT));
        } else {
            unregister_code16(LAG(KC_LEFT));
        }
        return false;
    default: // everything else Ctrl + Keycode
        if (record->event.pressed) {
            xprintf("%u pressed\n", keycode);
            register_code16(C(keycode));
        } else {
            if (keycode == 16416) { // handle the hold without pressing any other key and release
                return true;
            }
            xprintf("%u released\n", keycode);
            unregister_code16(C(keycode));
        }
        return false;
    }
}
