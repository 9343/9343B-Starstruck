#include "main.h"
#include "input.h"
#include "tick.h"
#include "util.h"
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
	else if(strcmp(inStr->command, "fsize ") == 0)
	{
		char filename[strlen(inStr->command - 7)];
		memcpy(&filename[0], &inStr->command[strlen(inStr->command - 7)], strlen(inStr->command - 7) + 1);

		FILE* f = fopen(filename, "r");
		char message[100];
		sprintf(message, "%d", fcount(f));
		writeJINXMessage(message);
	}
	else if(strcmp(inStr->command, "reboot ") == 0)
	{
		writeJINXMessage("Preparing for shutdown...");
		fdelete("autoprog");
		writeJINXMessage("Cortex is ready for power cycle.");
	}
	else if(strcmp(inStr->command, "backup ") == 0)
	{
		char filename[strlen(inStr->command - 7)];
		memcpy(&filename[0], &inStr->command[strlen(inStr->command - 7)], strlen(inStr->command - 7) + 1);

		FILE* in = fopen("autoprog", "r");
		FILE* out = fopen(filename, "w");
		size_t size = fcount(in);
		char buf[size];
		fread(&buf[0], size, 1, in);
		fwrite(&buf[0], size, 1, out);
	}
	else if(strcmp(inStr->command, "restore") == 0)
	{
		char filename[strlen(inStr->command - 7)];
		memcpy(&filename[0], &inStr->command[strlen(inStr->command - 7)], strlen(inStr->command - 7) + 1);

		FILE* in = fopen(filename, "r");
		FILE* out = fopen("autoprog", "w");
		size_t size = fcount(in);
		char buf[size];
		fread(&buf[0], size, 1, in);
		fwrite(&buf[0], size, 1, out);
	}
	else if(strcmp(inStr->command, "dump ") == 0)
	{
		char filename[strlen(inStr->command - 7)];
		memcpy(&filename[0], &inStr->command[strlen(inStr->command - 7)], strlen(inStr->command - 7) + 1);

		FILE* in = fopen(filename, "r");
		char message[(fcount(in) * 2) + 1];

		char* hex = "0123456789abcdef";
		int offset = 0;
		while(!feof(in))
		{
			char b;
			fread(&b, 1, 1, in);
			message[offset] = hex[b & 0xf];
			message[offset + 1] = hex[(b << 4) & 0xf];
			offset += 2;
		}

		writeJINXMessage(message);
	}
}

void initializeIO() {

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

		long sleepTime = DELAY_INTERVAL_MICRO - (micros() % DELAY_INTERVAL_MICRO);
		updateLcd(sleepTime);

		delayMicroseconds(sleepTime);
	}
}

void operatorControl() {
	writeJINXMessage("Starting driver...");
	joystick_setMode(JOYSTICK_MODE_DRIVER);
	while (true) {
		joystick_update();
		tick();

		long sleepTime = DELAY_INTERVAL_MICRO - (micros() % DELAY_INTERVAL_MICRO);
		updateLcd(sleepTime);

		delayMicroseconds(sleepTime);
	}
}

/*
int sleepTime = DELAY_INTERVAL_MICRO - (micros() % DELAY_INTERVAL_MICRO);
char string[14 + iLength(sleepTime)];
sprintf(string, "Delaying for %d", sleepTime);
writeJINXMessage(string);
*/
