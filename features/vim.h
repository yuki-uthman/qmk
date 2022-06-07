#include "motions.h"

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)

// Check to see if vim mode is enabled
bool vim_mode_enabled(void);
// Enable vim mode
void enable_vim_mode(void);
// Disable vim mode
void disable_vim_mode(void);
// Toggle vim mode
void toggle_vim_mode(void);

// Process keycode for vim mode
bool process_vim_mode(uint16_t keycode, const keyrecord_t *record);
