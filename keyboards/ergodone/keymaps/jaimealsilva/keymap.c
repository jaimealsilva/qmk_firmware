#include "version.h"
#include "led.h"
#include "jaimealsilva.c"

#define LEDC_TOP 20
#define LEDC_S 1
uint8_t ledc[2];

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    ergodox_led_all_off();
    ledc[0] = 0;
    ledc[1] = 0;
};

void drive_led(uint8_t l) {
    uint8_t i = l - 1;
    if (ledc[i] < LEDC_S) {
        ergodox_right_led_on(l);
    } else {
        ergodox_right_led_off(l);
    }
    ++ledc[i];
    if (ledc[i] >= LEDC_TOP) {
        ledc[i] = 0;
    }
}

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

    uint8_t layer = biton32(layer_state);

    ergodox_right_led_1_off();
    ergodox_right_led_3_off();
    switch (layer) {
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
