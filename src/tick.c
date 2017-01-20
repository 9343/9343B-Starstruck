#include "tick.h"
#include "main.h"
#include "input.h"
#include "util.h"

void tick() {
	// 1 3
	// 2 10

	motorSet(1,  -dewine(joystick_analog(3))
				- dewine(joystick_analog(4))
				- dewine(joystick_analog(1)));

	motorSet(2,   dewine(joystick_analog(3))
				- dewine(joystick_analog(4))
				+ dewine(joystick_analog(1)));

	motorSet(3,  -dewine(joystick_analog(3))
				+ dewine(joystick_analog(4))
				+ dewine(joystick_analog(1)));

	motorSet(10,  dewine(joystick_analog(3))
				+ dewine(joystick_analog(4))
				- dewine(joystick_analog(1)));

	int arm = 0;

	if (joystick_digital(5, JOY_UP)) {
		arm = 127;
	} else if (joystick_digital(5, JOY_DOWN)) {
		arm = -127;
	} else {
		arm = 0;
	}

	armSet(arm);

	if(joystick_digital(6, JOY_UP)) {
		motorSet(8, -127);
	} else if(joystick_digital(6, JOY_DOWN)) {
		motorSet(8, 127);
	} else {
		motorSet(8, 0);
	}

	lcdPrint(uart1, 1, "Main:   %d", powerLevelMain());
	lcdPrint(uart1, 2, "Backup: %d", analogRead(1));

	delay(10);
}
