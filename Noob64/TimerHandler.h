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
	TimerHandler(RCP&, R4300i&);

	inline int getTimer(void);					// Returns the current timer value
	inline void setTimer(int);					// Sets the current timer to the given value
	inline void decTimer(void);					// Updates the current timer - decreases it's value by TIME_UNIT
	inline int getNextTimer(int);				// Returns the next timer of the given type

	void reset(void);							// Clears the timer handler
	void change_compare_timer(void);			// Changes the value of the compare timer
	void change_timer(int Type, int Value);		// Changes the value of the timer of the given type
	void check_timer(void);						// Checks the value of every timer and updates the current timer accordingly
	void timer_done(void);						// Called when a timer has reached 0. Launches the related handler

	// Temporary workaround to trigger the PI timer from outside the class
	inline void force_pi_timer_done();

private:
	inline void compare_timer_done();			// Compare timer handler
	inline void si_timer_done();				// SI timer handler
	inline void pi_timer_done();				// PI timer handler
	inline void vi_timer_done();				// VI timer handler
	inline void rsp_timer_done();				// RSP timer handler

	RCP		&rcp;								// A reference to the RCP
	R4300i	&cpu;								// A reference to the CPU
	int		current_timer_type;					// The type of the current timer
	int		timer;								// The value of the current timer
	int		next_timer[MAX_TIMERS];				// The values of the next timers
	bool	active[MAX_TIMERS];					// A boolean representing whether a timer is active or not
};