/*
 * Noob64 - A Nintendo 64 emulator.
 *
 * (c) Copyright 2012 Quentin Metzler and 
 * Romain Richard.
 *
 * Permission to use, copy, modify and distribute Noob64 in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Noob64 is freeware for PERSONAL USE only. Commercial users should
 * seek permission of the copyright holders first. Commercial use includes
 * chwing money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

/*
 * The TimerHandler files contains the functions relative to the n64 timers
 * Like the VI timer which is useful to refresh the screen and RSP timer
 * to launch the emulation of the RSP thanks to the plugin.
 *
 */

#pragma once

// The different timer types
#define COMPARE_TIMER	0
#define SI_TIMER		1
#define PI_TIMER		2
#define VI_TIMER		3
#define RSP_TIMER		4
#define MAX_TIMERS		5

class TimerHandler
{
public:

	static inline int getTimer(void);					// Returns the current timer value
	static inline void setTimer(int);					// Sets the current timer to the given value
	static inline void decTimer(void);					// Updates the current timer - decreases it's value by TIME_UNIT
	static inline int getNextTimer(int);				// Returns the next timer of the given type

	void static reset(void);							// Clears the timer handler
	void static change_compare_timer(void);				// Changes the value of the compare timer
	void static change_timer(int Type, int Value);		// Changes the value of the timer of the given type
	void static check_timer(void);						// Checks the value of every timer and updates the current timer accordingly
	void static timer_done(void);						// Called when a timer has reached 0. Launches the related handler

	// Temporary workaround to trigger the PI timer from outside the class
	static inline void force_pi_timer_done();

private:
	static inline void compare_timer_done();			// Compare timer handler
	static inline void si_timer_done();					// SI timer handler
	static inline void pi_timer_done();					// PI timer handler
	static inline void vi_timer_done();					// VI timer handler
	static inline void rsp_timer_done();				// RSP timer handler

	static int	current_timer_type;						// The type of the current timer
	static int	timer;									// The value of the current timer
	static int	next_timer[MAX_TIMERS];					// The values of the next timers
	static bool	active[MAX_TIMERS];						// A boolean representing whether a timer is active or not
};