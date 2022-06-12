#pragma once

#include "quantum.h"

bool mac_layer_is_enabled(void);

void enable_mac_layer(void);

void disable_mac_layer(void);

void toggle_mac_layer(void);


bool process_mac_layer(uint16_t keycode, const keyrecord_t *record);
