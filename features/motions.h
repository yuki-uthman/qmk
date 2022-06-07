#pragma once

#include QMK_KEYBOARD_H

// The vim motions keys supported by single keystrokes/chords
#define VIM_H KC_LEFT
#define VIM_J KC_DOWN
#define VIM_K KC_UP
#define VIM_L KC_RIGHT

#define VIM_B LALT(KC_LEFT)
#define VIM_W LALT(KC_RIGHT)
#define VIM_E LALT(KC_RIGHT)

void register_motion(uint16_t keycode, const keyrecord_t *record);
