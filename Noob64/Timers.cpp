#include "StdAfx.h"

Timers::Timers()
{
}

void Timers::ChangeCompareTimer(word compare, word count)
{
	word NextCompare = compare - count;
	if ((NextCompare & 0x80000000) != 0)
		NextCompare = 0x7FFFFFFF;
	if (NextCompare == 0) 
		NextCompare = 0x1;
	ChangeTimer(CompareTimer,NextCompare, compare, count);
}

void Timers::ChangeTimer(int Type, int Value, word compare, word count)
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

void Timers::CheckTimer(word compare, word count)
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
		cerr << "No active timers ???\nEmulation Stoped" << endl;
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
	switch (timers->CurrentTimerType) 
	{
		case CompareTimer:
			Cause |= CAUSE_IP7;
			check_interrupt();
			timers->ChangeCompareTimer(Compare, Count);
			break;
		case SiTimer:
			timers->ChangeTimer(SiTimer, 0, Compare, Count);
			memory->mi_regs.setIntr(memory->mi_regs.getIntr() | MI_INTR_SI);
			memory->si_regs.setStatus(memory->si_regs.getStatus() | SI_STATUS_INTERRUPT);
			check_interrupt();
			break;
		case PiTimer:
			timers->ChangeTimer(PiTimer, 0, Compare, Count);
			memory->pi_regs.setStatus(memory->pi_regs.getStatus() & ~PI_STATUS_DMA_BUSY);
			memory->mi_regs.setIntr(memory->mi_regs.getIntr() | MI_INTR_PI);
			check_interrupt();
			break;
		case ViTimer:
			RefreshScreen();
			memory->mi_regs.setIntr(memory->mi_regs.getIntr() | MI_INTR_VI);
			check_interrupt();
			break;
		case RspTimer:
			timers->ChangeTimer(RspTimer,0, Compare, Count);
			//RunRsp();
			break;
	}
	timers->CheckTimer(Compare, Count);
}