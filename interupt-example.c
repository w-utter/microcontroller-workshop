#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

#define BUTTON_PIN 2
#define LED_PIN 3

// Debounce control
int state = 0;
const int delayTime = 100000; // Delay for every push button may vary
absolute_time_t time, curr_time;

void gpio_callback(uint gpio, uint32_t events) {
    curr_time = get_absolute_time();
    if (absolute_time_diff_us(time, curr_time) > delayTime) {
        time = get_absolute_time();;
        state = !state;
        gpio_put(LED_PIN, state);
    }
}

int main() {
    stdio_init_all();
    time = get_absolute_time();

    gpio_init(BUTTON_PIN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    
    while (true)
        printf("Hello GPIO IRQ\n");
}


