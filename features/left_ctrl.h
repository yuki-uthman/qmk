#pragma once

#include "quantum.h"

bool left_ctrl_is_enabled(void);

void enable_left_ctrl(void);

void disable_left_ctrl(void);

void toggle_left_ctrl(void);


bool process_left_ctrl(uint16_t keycode, const keyrecord_t *record);
