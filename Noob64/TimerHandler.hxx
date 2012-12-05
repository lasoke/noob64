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
 * charging money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#pragma once

#include "TimerHandler.h"

inline int TimerHandler::getTimer(void)			{ return timer; }
inline void TimerHandler::setTimer(int t)		{ timer = t; }
inline void TimerHandler::decTimer(void)		{ timer -= TIME_UNIT; }
inline int TimerHandler::getNextTimer(int type)	{ return next_timer[type]; }

inline void TimerHandler::compare_timer_done()
{
	R4300i::setCop0(CAUSE, R4300i::getCop0(CAUSE) | CAUSE_IP7);
	R4300i::check_interrupt();
	change_compare_timer();
}

inline void TimerHandler::si_timer_done()
{
	change_timer(SI_TIMER, 0);
	RCP::getMI()->setIntr(RCP::getMI()->getIntr() | MI_INTR_SI);
	RCP::getSI()->setStatus(RCP::getSI()->getStatus() | SI_STATUS_INTERRUPT);
	R4300i::check_interrupt();
}

inline void TimerHandler::pi_timer_done()
{
	change_timer(PI_TIMER, 0);
	RCP::getPI()->setStatus(RCP::getPI()->getStatus() & ~PI_STATUS_DMA_BUSY);
	RCP::getMI()->setIntr(RCP::getMI()->getIntr() | MI_INTR_PI);
	R4300i::check_interrupt();
}

inline void TimerHandler::vi_timer_done()
{
	RCP::refresh_screen();
	RCP::getMI()->setIntr(RCP::getMI()->getIntr() | MI_INTR_VI);
	R4300i::check_interrupt();
}

inline void TimerHandler::rsp_timer_done()
{
	change_timer(RSP_TIMER, 0);
	RCP::run_rsp();
}

inline void TimerHandler::force_pi_timer_done()
{
	RCP::getMI()->setIntr(RCP::getMI()->getIntr() & ~MI_INTR_VI);
	pi_timer_done();
	check_timer();
}
