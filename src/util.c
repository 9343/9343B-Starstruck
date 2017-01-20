#include <util.h>

int dewined(int x, int y) {
	if (x < y && x > -y) return 0;
	return x;
}

int dewine(int x) {
	return dewined(x, 20);
}

int maxd(int x, int y) {
	if (x > y) {
		return y;
	}

	if (x < -y) {
		return -y;
	}

	return x;
}

int max(int x) {
	return maxd(x, 127);
}

int min(int x, int y) {
	if (x < y) return y;
	return x;
}

void armSet(int arm) {
	motorSet(4, -arm);
	motorSet(5, arm);
	motorSet(6, arm);
	motorSet(7, -arm);
}
