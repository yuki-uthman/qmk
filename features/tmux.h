#pragma once

#include "quantum.h"

bool tmux_is_enabled(void);
void enable_tmux(void);
void disable_tmux(void);

bool process_tmux(uint16_t keycode, const keyrecord_t *record);
