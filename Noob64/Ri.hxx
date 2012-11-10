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

#include "Ri.h"

inline void RI_REGS::setMode(word w)			{ data.mode = w; }
inline void RI_REGS::setConfig(word w)			{ data.config = w; }
inline void RI_REGS::setCurrentLoad(word w)		{ data.current_load = w; }
inline void RI_REGS::setSelect(word w)			{ data.select = w; }
inline void RI_REGS::setRefresh(word w)			{ data.refresh = w; }
inline void RI_REGS::setLatency(word w)			{ data.latency = w; }
inline void RI_REGS::setRerror(word w)			{ data.rerror = w; }
inline void RI_REGS::setWerror(word w)			{ data.werror = w; }

inline word RI_REGS::getMode()					{ return data.mode; }
inline word RI_REGS::getConfig()				{ return data.config; }
inline word RI_REGS::getCurrentLoad()			{ return data.current_load; }
inline word RI_REGS::getSelect()				{ return data.select; }
inline word RI_REGS::getRefresh()				{ return data.refresh; }
inline word RI_REGS::getLatency()				{ return data.latency; }
inline word RI_REGS::getRerror()				{ return data.rerror; }
inline word RI_REGS::getWerror()				{ return data.werror; }

