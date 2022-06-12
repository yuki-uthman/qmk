SRC += features/casemodes.c
SRC += features/custom_shift_keys.c
SRC += features/abbreviation.c
SRC += features/motions.c
SRC += features/vim.c
SRC += features/left_ctrl.c
SRC += features/macOS.c

OLED_DRIVER = SSD1306

CONSOLE_ENABLE = yes
EXTRAKEY_ENABLE = no

KEY_OVERRIDE_ENABLE = yes
TAP_DANCE_ENABLE = yes
