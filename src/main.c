#include "main.h"
#include "input.h"
#include "tick.h"
#include "types.h"
#include "JINX.h"

void parseMessage(JINX* inStr)
{
	writeJINXMessage(inStr->command);

	if(strcmp(inStr->command, "record") == 0)
	{
		writeJINXMessage("Starting recording!");
		start_recording();
	}
	else if(strcmp(inStr->command, "stop") == 0)
	{
		writeJINXMessage("Stopping recording!");
		stop_recording();
	}
	else if(strcmp(inStr->command, "reload") == 0)
	{
		writeJINXMessage("Reloading...");
		autonomous_load();
	}
	else if(strcmp(inStr->command, "fsize") == 0)
	{
		FILE* f = fopen("autoprog", "r");
		char message[100];
		sprintf(message, "%d", fcount(f));
		writeJINXMessage(message);
	}
	else if(strcmp(inStr->command, "reboot") == 0)
	{
		writeJINXMessage("Preparing for shutdown...");
		fdelete("autoprog");
		writeJINXMessage("Cortex is ready for power cycle.");
	}
}

void initializeIO() {
	pinMode(10, INPUT);
}

void initialize() {
	setTeamName("9343B");

	initJINX(stdout);
	taskCreate(JINXRun, TASK_DEFAULT_STACK_SIZE, NULL, (TASK_PRIORITY_DEFAULT));

	autonomous_load();

	lcdInit(uart1);
	lcdClear(uart1);
	lcdSetBacklight(uart1, true);
}

void autonomous() {
	writeJINXMessage("Starting autonomous...");
	joystick_setMode(JOYSTICK_MODE_AUTO);
	while(true) {
		joystick_update();
		tick();
	}
}

void operatorControl() {
	writeJINXMessage("Starting driver...");
	joystick_setMode(JOYSTICK_MODE_DRIVER);
	while (true) {
		joystick_update();
		tick();
	}
}
