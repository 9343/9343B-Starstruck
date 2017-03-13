#include "types.h"

#define JOYSTICK_MODE_AUTO 1
#define JOYSTICK_MODE_DRIVER 0
#define DELAY_INTERVAL_MICRO 10000

void autonomous_load(); // Loads autonomous from autoprog.
void start_recording(); // Starts recording a new autonomous program.
void stop_recording(); // Stops the current recording.

void joystick_setMode(int mode); // Sets the mode between autonomous and driver.
void joystick_update(); // Updates the joystick values. Reads from memory for autonomous, and controller for driver.
int joystick_analog(u8 axis); // Returns the value of an analog axis on the controller.
int joystick_digital(u8 button_group, u8 button); // Returns the value of a digital button.
