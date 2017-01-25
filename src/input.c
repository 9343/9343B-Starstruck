#include "main.h"
#include "types.h"
#include "input.h"
#include "JINX.h"

JoystickState current_state;
int current_mode;

JoystickState* autonomous_prog;
u64 autonomous_frame;
u64 max_frames;

bool auto_enabled;

FILE* f;

bool RECORDING;

void autonomous_load() {
	RECORDING = false;
	writeJINXMessage("Loading autonomous program...");

	f = fopen("autoprog", "r");
	autonomous_prog = (JoystickState*)malloc(fcount(f)); // Allocates memory for the autonomous inputs.
	max_frames = fcount(f) / 8;
	fread(autonomous_prog, 1, fcount(f), f); // Reads autonomous program into memory.

	auto_enabled = true;
	fclose(f);
}

void start_recording() {
	f = fopen("autoprog", "w");
	RECORDING = true;
}

void stop_recording() {
	RECORDING = false;
	fclose(f);
	f = NULL;
}

void joystick_setMode(int mode) {
	current_mode = mode;
	autonomous_frame = 0;
}

void joystick_update() {
	if(current_mode != JOYSTICK_MODE_AUTO) {
		current_state.axes[0] = joystickGetAnalog(1, 1);
		current_state.axes[1] = joystickGetAnalog(1, 2);
		current_state.axes[2] = joystickGetAnalog(1, 3);
		current_state.axes[3] = joystickGetAnalog(1, 4);
		current_state.accel_x = joystickGetAnalog(1, ACCEL_X);
		current_state.accel_y = joystickGetAnalog(1, ACCEL_Y);

		current_state.button_mask.g5 = 0;
		current_state.button_mask.g6 = 0;
		current_state.button_mask.g7 = 0;
		current_state.button_mask.g8 = 0;

		current_state.button_mask.g5 += joystickGetDigital(1, 5, JOY_UP) * JOY_UP;
		current_state.button_mask.g5 += joystickGetDigital(1, 5, JOY_DOWN) * JOY_DOWN;

		current_state.button_mask.g6 += joystickGetDigital(1, 6, JOY_UP) * JOY_UP;
		current_state.button_mask.g6 += joystickGetDigital(1, 6, JOY_DOWN) * JOY_DOWN;

		current_state.button_mask.g7 += joystickGetDigital(1, 7, JOY_UP) * JOY_UP;
		current_state.button_mask.g7 += joystickGetDigital(1, 7, JOY_LEFT) * JOY_LEFT;
		current_state.button_mask.g7 += joystickGetDigital(1, 7, JOY_DOWN) * JOY_DOWN;
		current_state.button_mask.g7 += joystickGetDigital(1, 7, JOY_RIGHT) * JOY_RIGHT;

		current_state.button_mask.g8 += joystickGetDigital(1, 8, JOY_UP) * JOY_UP;
		current_state.button_mask.g8 += joystickGetDigital(1, 8, JOY_LEFT) * JOY_LEFT;
		current_state.button_mask.g8 += joystickGetDigital(1, 8, JOY_DOWN) * JOY_DOWN;
		current_state.button_mask.g8 += joystickGetDigital(1, 8, JOY_RIGHT) * JOY_RIGHT;

		if(RECORDING) {
			// Writes the controller state to the file.
			fwrite(&current_state, 8, 1, f);
			fflush(f);
		}
	} else {
		if(auto_enabled) {
			if(autonomous_frame < max_frames) {
				if(!(analogRead(1) > 1360 && analogRead(1) < 2730)) {
					// Copy current autonomous inputs from memory.
					memcpy(&current_state, &autonomous_prog[autonomous_frame], 8);
					autonomous_frame++;

					if(analogRead(1) > 2730) {
						current_state.axes[0] = -current_state.axes[0];
						current_state.axes[3] = -current_state.axes[3];
					}
				} else {
					memset(&current_state, 0, 8);
				}
			} else {
				memset(&current_state, 0, 8);
			}
		} else {
			memset(&current_state, 0, 8);
		}
	}
}

int joystick_analog(u8 axis) {
	return current_state.axes[axis - 1];
}

int joystick_digital(u8 button_group, u8 button) {
	switch(button_group)
	{
	case 5:
		return ((current_state.button_mask.g5 & button) != 0 ? 1 : 0);
	case 6:
		return ((current_state.button_mask.g6 & button) != 0 ? 1 : 0);
		break;
	case 7:
		return ((current_state.button_mask.g7 & button) != 0 ? 1 : 0);
		break;
	case 8:
		return ((current_state.button_mask.g8 & button) != 0 ? 1 : 0);
		break;
	}

	return 0;
}
