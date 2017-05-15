#include "tick.h"
#include "main.h"
#include "input.h"
#include "util.h"

void tick() {
	// 7 3
	// 2 9

	// Wheels
	motorSet(7,  -(-dewine(joystick_analog(3))
				- dewine(joystick_analog(4))
				- dewine(joystick_analog(1))));

	motorSet(2,   dewine(joystick_analog(3))
				- dewine(joystick_analog(4))
				+ dewine(joystick_analog(1)));

	motorSet(3,  -dewine(joystick_analog(3))
				+ dewine(joystick_analog(4))
				+ dewine(joystick_analog(1)));

	motorSet(9,  -(dewine(joystick_analog(3))
				+ dewine(joystick_analog(4))
				- dewine(joystick_analog(1))));

	/**
	motorSet(10, dewine(joystick_analog(3))
				+ dewine(joystick_analog(4))
				- dewine(joystick_analog(1)));
				**/

	// Arm
	int arm = 0;

	if (joystick_digital(5, JOY_UP)) {
		arm = 127;
	} else if (joystick_digital(5, JOY_DOWN)) {
		arm = -127;
	} else {
		arm = 0;
	}

	motorSet(4, arm);
	motorSet(5, -arm);
	motorSet(6, -arm);
	//motorSet(7, arm);

	// Claw
	if(joystick_digital(6, JOY_UP)) {
		motorSet(8, -127);
	} else if(joystick_digital(6, JOY_DOWN)) {
		motorSet(8, 127);
	} else {
		motorSet(8, 0);
	}
}
