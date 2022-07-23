#pragma once

#include "quantum.h"

bool right_ctrl_is_enabled(void);

void enable_right_ctrl(void);

void disable_right_ctrl(void);

void toggle_right_ctrl(void);


bool process_right_ctrl(uint16_t keycode, const keyrecord_t *record);
