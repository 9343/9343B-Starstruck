#include "main.h"
#include "input.h"
#include "tick.h"
#include "term.h"
#include "util.h"
#include "types.h"
#include "lcd.h"

void initializeIO() {}

void initialize() {
	setTeamName("9343B");
	auto_init();
	term_init();
	lcd_init();
}

void autonomous() {
	printf("Starting autonomous...");
	joystick_setMode(JOYSTICK_MODE_AUTO);
	while(true) {
		joystick_update();
		tick();

		long sleepTime = DELAY_INTERVAL_MICRO - (micros() % DELAY_INTERVAL_MICRO);
		delayMicroseconds(sleepTime);
	}
}

void operatorControl() {
	printf("Starting driver...");
	joystick_setMode(JOYSTICK_MODE_DRIVER);
	while (true) {
		joystick_update();
		tick();

		long sleepTime = DELAY_INTERVAL_MICRO - (micros() % DELAY_INTERVAL_MICRO);
		delayMicroseconds(sleepTime);
	}
}
