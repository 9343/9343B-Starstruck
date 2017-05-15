#include "util.h"

int dewined(int x, int y) {
	if (x < y && x > -y) return 0;
	return x;
}

int dewine(int x) {
	return dewined(x, 20);
}
