#include "version.h"
#include "led.h"
#include "jaimealsilva.c"

#define LEDC_TOP 20
#define LEDC_S 1
uint8_t ledc[2];

/* false: Caps Lock LED is off
   true: Caps Lock LED is on */
bool CAPS_LED = false;

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
    switch (keycode) {
      case KC_CAPS:
        if (record->event.pressed) {
          // Turn LED1 On/Off for Caps Lock
          if (CAPS_LED) {
            ergodox_right_led_3_off();
            ergodox_board_led_off();
            CAPS_LED = false;
          } else {
            ergodox_right_led_3_on();
            ergodox_board_led_on();
            CAPS_LED = true;
          }
        }
        return true;

      // For vim: turn down caps lock at esc
      case KC_ESC:
        if (CAPS_LED) {
            tap_code(KC_CAPS);
            ergodox_right_led_3_off();
            ergodox_board_led_off();
            CAPS_LED = false;
        }
        return true;
    }
    return true;
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    switch (layer) {
        case 1:
            drive_led(1);
            break;
        case 2:
            drive_led(2);
            break;
        default:
            // none
            break;
    }

};

/* bool led_update_user(led_t led_state) { */
/*     if (led_state.num_lock) { */
/*         ergodox_right_led_3_on(); */
/*     } else { */
/*         ergodox_right_led_3_off(); */
/*     } */
/*     return true; */
/* } */
