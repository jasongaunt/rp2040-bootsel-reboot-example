#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "bootsel-reboot.hpp"

const uint LED_PIN = 25;

struct repeating_timer timer;
volatile bool timer_fired = false;
bool led_state = false;

bool flip_leds(struct repeating_timer *t) { timer_fired = true; return true; }

int main() {
	stdio_init_all();
	arm_watchdog();

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	add_repeating_timer_ms(500, flip_leds, NULL, &timer);

	puts("Hello World\n");

	while (1) {
		check_bootsel_button();

		if (timer_fired) {
			led_state = !led_state;
			timer_fired = false;
			gpio_put(LED_PIN, led_state);
		}
	}
}
