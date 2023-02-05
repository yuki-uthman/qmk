SRC += features/caps_word.c
# SRC += features/abbreviation.c
SRC += features/motions.c
SRC += features/right_ctrl.c
SRC += features/left_ctrl.c
SRC += features/tmux.c

OLED_DRIVER = SSD1306

CONSOLE_ENABLE = yes
EXTRAKEY_ENABLE = no

KEY_OVERRIDE_ENABLE = yes
TAP_DANCE_ENABLE = no
