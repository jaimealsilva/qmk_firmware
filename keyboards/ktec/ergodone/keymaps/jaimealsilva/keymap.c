#include QMK_KEYBOARD_H
#include "version.h"
#include "ergodox_compat.h"
#include "host.h"
#include "jaimealsilva.c"

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    ergodox_led_all_off();
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    led_t leds;
    switch (keycode) {
      // For vim: turn down caps lock at esc
      case KC_ESC:
        leds = host_keyboard_led_state();
        if (leds.caps_lock) {
            tap_code(KC_CAPS);
        }
        return true;
    }
    return true;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    led_t leds = host_keyboard_led_state();
    if (leds.caps_lock) {
        ergodox_right_led_2_on();
        ergodox_board_led_on();
    } else {
        ergodox_right_led_2_off();
        ergodox_board_led_off();
    }

    ergodox_right_led_1_off();
    ergodox_right_led_3_off();

    switch (get_highest_layer(layer_state)) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }
};
