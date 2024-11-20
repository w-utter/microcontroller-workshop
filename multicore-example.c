#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#define LED_PINA 3
#define LED_PINB 4

void core1_entry() {
    while(1) {
        printf("Hello Core1\n");
        gpio_put(LED_PINB, 0);
        sleep_ms(1000);
        gpio_put(LED_PINB, 1);
        sleep_ms(1000);
    }     
}

int main() {
    stdio_init_all();
    printf("Hello, multicore!\n");
    multicore_launch_core1(core1_entry);

    gpio_init(LED_PINA);
    gpio_init(LED_PINB);
    gpio_set_dir(LED_PINA, GPIO_OUT);
    gpio_set_dir(LED_PINB, GPIO_OUT);

    while(1) {
        printf("Hello Core0\n");
        gpio_put(LED_PINA, 0);
        sleep_ms(1000);
        gpio_put(LED_PINA, 1);
        sleep_ms(1000);
    }
}