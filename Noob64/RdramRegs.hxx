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

#include "RdramRegs.h"

inline void RDRAM_REGS::setConfig(word w)		{ data.config = w; }
inline void RDRAM_REGS::setDeviceId(word w)		{ data.device_id = w; }
inline void RDRAM_REGS::setDelay(word w)		{ data.delay = w; }
inline void RDRAM_REGS::setMode(word w)			{ data.mode = w; }
inline void RDRAM_REGS::setRefInterval(word w)	{ data.ref_interval = w; }
inline void RDRAM_REGS::setRefRow(word w)		{ data.ref_row = w; }
inline void RDRAM_REGS::setRasInterval(word w)	{ data.ras_interval = w; }
inline void RDRAM_REGS::setMinInterval(word w)	{ data.min_interval = w; }
inline void RDRAM_REGS::setAddrSelect(word w)	{ data.addr_select = w; }
inline void RDRAM_REGS::setDeviceManuf(word w)	{ data.device_manuf = w; }

inline word RDRAM_REGS::getConfig()				{ return data.config; }
inline word RDRAM_REGS::getDeviceId()			{ return data.device_id; }
inline word RDRAM_REGS::getDelay()				{ return data.delay; }
inline word RDRAM_REGS::getMode()				{ return data.mode; }
inline word RDRAM_REGS::getRefInterval()		{ return data.ref_interval; }
inline word RDRAM_REGS::getRefRow()				{ return data.ref_row; }
inline word RDRAM_REGS::getRasInterval()		{ return data.ras_interval; }
inline word RDRAM_REGS::getMinInterval()		{ return data.min_interval; }
inline word RDRAM_REGS::getAddrSelect()			{ return data.addr_select; }
inline word RDRAM_REGS::getDeviceManuf()		{ return data.device_manuf; }