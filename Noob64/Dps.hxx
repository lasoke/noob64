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

#include "Dps.h"

inline void DPS::setTbist(word w)			{ data.tbist = w; }
inline void DPS::setTestMode(word w)		{ data.test_mode = w; }
inline void DPS::setBufTestAddr(word w)	{ data.buftest_addr = w; }
inline void DPS::setBufTestData(word w)	{ data.buftest_data = w; }

inline word DPS::getTbist()				{ return data.tbist; }
inline word DPS::getTestMode()				{ return data.test_mode; }
inline word DPS::getBufTestAddr()			{ return data.buftest_addr; }
inline word DPS::getBufTestData()			{ return data.buftest_data; }