#include "vim.h"

/* return false to finish processing of the key */
/* return true to fall through to the qmk processing of the key */

bool process_vim_mode(uint16_t keycode, keyrecord_t *record) {

    if (vim_disabled()) { return true; }
    switch (keycode) {
    case KC_W:
      if (record->event.pressed) {
          VIM_WORD();
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
    }
}
