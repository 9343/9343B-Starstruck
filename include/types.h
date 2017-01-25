#pragma once

/**
 * Typedefs to simplify
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long s64;

/** This struct represents the state of a single controller.
 *  Stored as a 64-bit type.
 */
typedef struct {
	s8 axes[4];
	s8 accel_x;
	s8 accel_y;
	struct {
		s8 g5 : 4;
		s8 g6 : 4;
		s8 g7 : 4;
		s8 g8 : 4;
	} __attribute__((packed)) button_mask;
} __attribute__((packed)) JoystickState;
