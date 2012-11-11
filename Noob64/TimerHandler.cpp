#include "StdAfx.h"

TimerHandler::TimerHandler()
{
}

void TimerHandler::reset(void)
{
	current_timer_type = -1;
	timer = 0;
	for (int i = 0; i < MAX_TIMERS; ++i) 
		active[i]= FALSE;
	change_timer(VI_TIMER, 5000, 0/*Compare*/, 0/*Count*/); 
	change_compare_timer(0/*Compare*/, 0/*Count*/);
}

void TimerHandler::change_compare_timer(word compare, word count)
{
	word NextCompare = compare - count;
	if ((NextCompare & 0x80000000) != 0)
		NextCompare = 0x7FFFFFFF;
	if (NextCompare == 0) 
		NextCompare = 0x1;
	change_timer(COMPARE_TIMER,NextCompare, compare, count);
}

void TimerHandler::change_timer(int type, int value, word compare, word count)
{	
	if (value == 0) 
	{ 
		next_timer[type] = 0;
		active[type] = false; 
		return;
	}
	next_timer[type] = value - timer;
	active[type] = true;
	check_timer(compare, count);
}

void TimerHandler::check_timer(word compare, word count)
{
	int i;

	for (i = 0; i < MAX_TIMERS; i++) 
	{
		if (!active[i])
			continue;
		if (!(i == COMPARE_TIMER && next_timer[i] == 0x7FFFFFFF))
			next_timer[i] += timer;
	}
	current_timer_type = -1;
	timer = 0x7FFFFFFF;
	for (i = 0; i < MAX_TIMERS; i++) 
	{
		if (next_timer[i] >= timer || !active[i])
			continue;
		timer = next_timer[i];
		current_timer_type = i;
	}
	if (current_timer_type == -1) 
	{
		cerr << "No active timer_handler ???\nEmulation Stoped" << endl;
		ExitThread(0);
	}
	for (i = 0; i < MAX_TIMERS; i++)
	{
		if (!active[i]) 
			continue;
		if (!(i == COMPARE_TIMER && next_timer[i] == 0x7FFFFFFF))
			next_timer[i] -= timer;
	}
	
	if (next_timer[COMPARE_TIMER] == 0x7FFFFFFF) 
	{
		word NextCompare = compare - count;
		if ((NextCompare & 0x80000000) == 0 && NextCompare != 0x7FFFFFFF)
			change_compare_timer(compare, count);
	}
}

void R4300i::timer_done()
{
	switch (timer_handler.current_timer_type) 
	{
		case COMPARE_TIMER:
			Cause |= CAUSE_IP7;
			check_interrupt();
			timer_handler.change_compare_timer(Compare, Count);
			break;
		case SI_TIMER:
			timer_handler.change_timer(SI_TIMER, 0, Compare, Count);
			rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_SI);
			rcp.getSI().setStatus(rcp.getSI().getStatus() | SI_STATUS_INTERRUPT);
			check_interrupt();
			break;
		case PI_TIMER:
			timer_handler.change_timer(PI_TIMER, 0, Compare, Count);
			rcp.getPI().setStatus(rcp.getPI().getStatus() & ~PI_STATUS_DMA_BUSY);
			rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_PI);
			check_interrupt();
			break;
		case VI_TIMER:
			rcp.refresh_screen();
			rcp.getMI().setIntr(rcp.getMI().getIntr() | MI_INTR_VI);
			check_interrupt();
			break;
		case RSP_TIMER:
			timer_handler.change_timer(RSP_TIMER,0, Compare, Count);
			rcp.run();
			break;
	}
	timer_handler.check_timer(Compare, Count);
}