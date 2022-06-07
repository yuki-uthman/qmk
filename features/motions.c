#include "motions.h"

void register_motion(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}
