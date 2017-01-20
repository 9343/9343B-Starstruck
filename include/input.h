#include "types.h"

#define JOYSTICK_MODE_AUTO 1
#define JOYSTICK_MODE_DRIVER 0

void autonomous_load();
void start_recording();
void stop_recording();
bool enabled();

void joystick_setMode(int mode);
void joystick_update();
int joystick_analog(u8 axis);
int joystick_digital(u8 button_group, u8 button);
