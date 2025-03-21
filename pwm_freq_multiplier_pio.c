#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "blink.pio.h"

#define INPUT_PIN 15  // Pin for 20 kHz input clock
#define OUTPUT_PIN 16 // Pin for 200 kHz output pulses
void pwm_freq_multiplier_pio_init(PIO pio, uint sm, uint offset, uint pwm_pin, uint trigger_pin){
    // Set the PWM pin to be controlled by the PIO
    pio_gpio_init(pio, pwm_pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pwm_pin, 1, true);

    // Set the trigger pin as input
    pio_gpio_init(pio, trigger_pin);
    gpio_set_dir(trigger_pin, GPIO_IN);

    // Configure the state machine
    pio_sm_config c = blink_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pwm_pin);
    sm_config_set_out_pins(&c, pwm_pin, 1);
    sm_config_set_set_pins(&c, pwm_pin, 1);
    sm_config_set_in_pins(&c, trigger_pin);

    // Set the clock divider to achieve 200 kHz frequency
    // Assuming the system clock is 125 MHz, the divider should be 125 MHz / 200 kHz / 20 = 31.25     20 cpu cycles per pio cycle
    sm_config_set_clkdiv(&c, 31.25f);

    // Initialize the state machine with the configuration
    pio_sm_init(pio, sm, offset, &c);

    // Enable the state machine
    pio_sm_set_enabled(pio, sm, true);
}
int main() {
    stdio_init_all();
    
    // Load PIO program
    PIO pio = pio0;  // Using PIO 0
    uint offset = pio_add_program(pio, &blink_program);
    uint sm = pio_claim_unused_sm(pio, true);
    printf("Program started...\n");
    printf("PIO program loaded at offset %u\n", offset);
    printf("State machine %u enabled\n", sm);
    //start the PIO state machine
    pwm_freq_multiplier_pio_init(pio, sm, offset, OUTPUT_PIN, INPUT_PIN);
    // Main loop (no code needed as PIO handles everything)
    while (1) {
        tight_loop_contents(); // Keep the main loop running, but idle
    }
    return 0;
}