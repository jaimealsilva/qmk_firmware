#include "version.h"

#include "jaimealsilva.c"

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    ergodox_board_led_on();
    ergodox_right_led_3_on();
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
