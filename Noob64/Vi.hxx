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

#include "Vi.h"

inline void VI_REGS::setStatus(word w)
{
	data.status = w;
	//ViStatusChanged
}
inline void VI_REGS::setOrigin(word w)			{ data.origin = w; }
inline void VI_REGS::setWidth(word w)
{
	data.width = w;
	//ViWidthChanged
}
inline void VI_REGS::setVintr(word w)			{ /*TODO*/ }
inline void VI_REGS::setCurrent(word w)			{ data.current = w; }
inline void VI_REGS::setBurst(word w)			{ data.burst = w; }
inline void VI_REGS::setVsync(word w)			{ data.v_sync = w; }
inline void VI_REGS::setHsync(word w)			{ data.h_sync = w; }
inline void VI_REGS::setLeap(word w)			{ data.leap = w; }
inline void VI_REGS::setHstart(word w)			{ data.h_start = w; }
inline void VI_REGS::setVstart(word w)			{ data.v_start = w; }
inline void VI_REGS::setVburst(word w)			{ data.v_burst = w; }
inline void VI_REGS::setXscale(word w)			{ data.x_scale = w; }
inline void VI_REGS::setYscale(word w)			{ data.y_scale = w; }

inline word VI_REGS::getStatus()				{ return data.status; }
inline word VI_REGS::getOrigin()				{ return data.origin; }
inline word VI_REGS::getWidth()					{ return data.width; }
inline word VI_REGS::getIntr()					{ return data.intr; }
inline word VI_REGS::getCurrent()				{ return data.current; }
inline word VI_REGS::getBurst()					{ return data.burst; }
inline word VI_REGS::getVsync()					{ return data.v_sync; }
inline word VI_REGS::getHsync()					{ return data.h_sync; }
inline word VI_REGS::getLeap()					{ return data.leap; }
inline word VI_REGS::getHstart()				{ return data.h_start; }
inline word VI_REGS::getVstart()				{ return data.v_start; }
inline word VI_REGS::getVburst()				{ return data.v_burst; }
inline word VI_REGS::getXscale()				{ return data.x_scale; }
inline word VI_REGS::getYscale()				{ return data.y_scale; }