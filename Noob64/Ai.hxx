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

#include "Ai.h"

inline void AI::setDramAddr(word w)			{ data.dram_addr = w; }
inline void AI::setLen(word w)				{ data.len = w; }
inline void AI::setControl(word w)			{ data.control = w & 0x1; }
inline void AI::setStatus(word w)			{ data.status = w; } 
inline void AI::setDacrate(word w)			{ data.dacrate = w; }
inline void AI::setBitrate(word w)			{ data.bitrate = w; }

inline word AI::getDramAddr()				{ return data.dram_addr; }
inline word AI::getLen()					{ return data.len; }
inline word AI::getControl()				{ return data.control; }
inline word AI::getStatus()					{ return data.status; }
inline word AI::getDacrate()				{ return data.dacrate; }
inline word AI::getBitrate()				{ return data.bitrate; }