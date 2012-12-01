#include "StdAfx.h"

TimerHandler::TimerHandler(RCP& rcp, R4300i& cpu) : rcp(rcp), cpu(cpu) {}

void TimerHandler::reset(void)
{
	current_timer_type = -1;
	timer = 0;
	for (int i = 0; i < MAX_TIMERS; ++i) 
		active[i]= FALSE;
	change_timer(VI_TIMER, 5000); 
	change_compare_timer();
}

void TimerHandler::change_compare_timer()
{
	word NextCompare = cpu.getCop0(COMPARE) - cpu.getCop0(COUNT);
	if ((NextCompare & 0x80000000) != 0)
		NextCompare = 0x7FFFFFFF;
	if (NextCompare == 0) 
		NextCompare = 0x1;
	change_timer(COMPARE_TIMER, NextCompare);
}

void TimerHandler::change_timer(int type, int value)
{	
	if (value == 0) 
	{ 
		next_timer[type] = 0;
		active[type] = false; 
		return;
	}
	next_timer[type] = value - timer;
	active[type] = true;
	check_timer();
}

void TimerHandler::check_timer()
{
	for (int i = 0; i < MAX_TIMERS; i++)
	{
		if (!active[i])
			continue;
		if (!(i == COMPARE_TIMER && next_timer[i] == 0x7FFFFFFF))
			next_timer[i] += timer;
	}
	current_timer_type = -1;
	timer = 0x7FFFFFFF;
	for (int i = 0; i < MAX_TIMERS; i++)
	{
		if (next_timer[i] >= timer || !active[i])
			continue;
		timer = next_timer[i];
		current_timer_type = i;
	}
	if (current_timer_type == -1)
		throw TIMER_BROKEN;
	for (int i = 0; i < MAX_TIMERS; i++)
	{
		if (!active[i]) 
			continue;
		if (!(i == COMPARE_TIMER && next_timer[i] == 0x7FFFFFFF))
			next_timer[i] -= timer;
	}
	
	if (next_timer[COMPARE_TIMER] == 0x7FFFFFFF)
	{
		word NextCompare = cpu.getCop0(COMPARE) - cpu.getCop0(COUNT);
		if (!(NextCompare & 0x80000000) && NextCompare != 0x7FFFFFFF)
			change_compare_timer();
	}
}

void TimerHandler::timer_done()
{
	switch (current_timer_type) 
	{
		case COMPARE_TIMER:
			compare_timer_done();
			break;
		case SI_TIMER:
			si_timer_done();
			break;
		case PI_TIMER:
			pi_timer_done();
			break;
		case VI_TIMER:
			vi_timer_done();
			break;
		case RSP_TIMER:
			rsp_timer_done();
			break;
	}
	check_timer();
}
