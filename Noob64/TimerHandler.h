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
	TimerHandler(RCP&, R4300i&);

	inline int getTimer(void);
	inline void setTimer(int);
	inline void decTimer(void);
	inline int getNextTimer(int);

	void reset(void);
	void change_compare_timer(void);
	void change_timer(int Type, int Value);
	void check_timer(void);
	void timer_done(void);

private:
	RCP		&rcp;
	R4300i	&cpu;
	int		current_timer_type;
	int		timer;
	int		next_timer[MAX_TIMERS];
	bool	active[MAX_TIMERS];
};