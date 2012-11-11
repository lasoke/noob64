#pragma once

#define COMPARE_TIMER	0
#define SI_TIMER		1
#define PI_TIMER		2
#define VI_TIMER		3
#define RSP_TIMER		4
#define MAX_TIMERS		5

class TimerHandler
{
public:
	TimerHandler();

	void reset(void);

	void change_compare_timer(word compare, word count);
	void change_timer (int Type, int Value, word compare, word count);
	void check_timer(word compare, word count);

	int  current_timer_type;
	int  timer;
	int  next_timer[MAX_TIMERS];
	bool active[MAX_TIMERS];
};