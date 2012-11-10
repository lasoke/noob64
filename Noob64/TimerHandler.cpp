#include "StdAfx.h"

TimerHandler::TimerHandler()
{
}

void TimerHandler::ChangeCompareTimer(word compare, word count)
{
	word NextCompare = compare - count;
	if ((NextCompare & 0x80000000) != 0)
		NextCompare = 0x7FFFFFFF;
	if (NextCompare == 0) 
		NextCompare = 0x1;
	ChangeTimer(CompareTimer,NextCompare, compare, count);
}

void TimerHandler::ChangeTimer(int Type, int Value, word compare, word count)
{	
	if (Value == 0) 
	{ 
		NextTimer[Type] = 0;
		Active[Type] = false; 
		return;
	}
	NextTimer[Type] = Value - Timer;
	Active[Type] = true;
	CheckTimer(compare, count);
}

void TimerHandler::CheckTimer(word compare, word count)
{
	int i;

	for (i = 0; i < MaxTimers; i++) 
	{
		if (!Active[i])
			continue;
		if (!(i == CompareTimer && NextTimer[i] == 0x7FFFFFFF))
			NextTimer[i] += Timer;
	}
	CurrentTimerType = -1;
	Timer = 0x7FFFFFFF;
	for (i = 0; i < MaxTimers; i++) 
	{
		if (NextTimer[i] >= Timer || !Active[i])
			continue;
		Timer = NextTimer[i];
		CurrentTimerType = i;
	}
	if (CurrentTimerType == -1) 
	{
		cerr << "No active timer_handler ???\nEmulation Stoped" << endl;
		ExitThread(0);
	}
	for (i = 0; i < MaxTimers; i++)
	{
		if (!Active[i]) 
			continue;
		if (!(i == CompareTimer && NextTimer[i] == 0x7FFFFFFF))
			NextTimer[i] -= Timer;
	}
	
	if (NextTimer[CompareTimer] == 0x7FFFFFFF) 
	{
		word NextCompare = compare - count;
		if ((NextCompare & 0x80000000) == 0 && NextCompare != 0x7FFFFFFF)
			ChangeCompareTimer(compare, count);
	}
}

void R4300i::TimerDone()
{
	switch (timer_handler.CurrentTimerType) 
	{
		case CompareTimer:
			Cause |= CAUSE_IP7;
			check_interrupt();
			timer_handler.ChangeCompareTimer(Compare, Count);
			break;
		case SiTimer:
			timer_handler.ChangeTimer(SiTimer, 0, Compare, Count);
			rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_SI);
			rcp.si.setStatus(rcp.si.getStatus() | SI_STATUS_INTERRUPT);
			check_interrupt();
			break;
		case PiTimer:
			timer_handler.ChangeTimer(PiTimer, 0, Compare, Count);
			rcp.pi.setStatus(rcp.pi.getStatus() & ~PI_STATUS_DMA_BUSY);
			rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_PI);
			check_interrupt();
			break;
		case ViTimer:
			//RefreshScreen();
			rcp.mi.setIntr(rcp.mi.getIntr() | MI_INTR_VI);
			check_interrupt();
			break;
		case RspTimer:
			timer_handler.ChangeTimer(RspTimer,0, Compare, Count);
			//RunRsp();
			break;
	}
	timer_handler.CheckTimer(Compare, Count);
}