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

#include "Dpc.h"

inline void DPC::setStart(word w)			{ data.start = w; }
inline void DPC::setEnd(word w)			{ data.end = w; }
inline void DPC::setCurrent(word w)		{ data.current = w; }
inline void DPC::setStatus(word w)			{ data.status = w; }
inline void DPC::setClock(word w)			{ data.clock = w; }
inline void DPC::setBufBusy(word w)		{ data.bufbusy = w; }
inline void DPC::setPipeBusy(word w)		{ data.pipebusy = w; }
inline void DPC::setTmem(word w)			{ data.tmem = w; }

inline word DPC::getStart()				{ return data.start; }
inline word DPC::getEnd()					{ return data.end; }
inline word DPC::getCurrent()				{ return data.current; }
inline word DPC::getStatus()				{ return data.status; }
inline word DPC::getClock()				{ return data.clock; }
inline word DPC::getBufBusy()				{ return data.bufbusy; }
inline word DPC::getPipeBusy()				{ return data.pipebusy; }
inline word DPC::getTmem()					{ return data.tmem; }