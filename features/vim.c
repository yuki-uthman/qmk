#include "vim.h"
#include "motions.h"


static bool vim_enabled = false;

// Check to see if vim mode is enabled
bool vim_mode_enabled(void) {
    return vim_enabled;
}
// Enable vim mode
void enable_vim_mode(void) {
    vim_enabled = true;
    /* normal_mode(); */
}
// Disable vim mode
void disable_vim_mode(void) {
    vim_enabled = false;
}
// Toggle vim mode
void toggle_vim_mode(void) {
    if (vim_enabled) {
        disable_vim_mode();
    }
    else {
        enable_vim_mode();
    }
}

/* return false to finish processing of the key */
/* return true to fall through to the qmk processing of the key */

bool process_vim_mode(uint16_t keycode, const keyrecord_t *record) {

    if (!vim_mode_enabled()) { return true; }

    switch (keycode) {
    case KC_W:
        register_motion(VIM_W, record);
        return false;
    case KC_B:
        register_motion(VIM_B, record);
        return false;
    case KC_H:
        register_motion(VIM_H, record);
        return false;
    case KC_J:
        register_motion(VIM_J, record);
        return false;
    case KC_K:
        register_motion(VIM_K, record);
        return false;
    case KC_L:
        register_motion(VIM_L, record);
        return false;
    case KC_SLSH:
        tap_code16(LGUI(KC_F));
        disable_vim_mode();
        return false;
    default:
      return true; // Process all other keycodes normally
    }
}
