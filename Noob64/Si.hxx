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

#include "Si.h"

inline void SI::setDramAddr(word w)		{ data.dram_addr = w; }
inline void SI::setPifAddrRd64b(word w)	{ data.pif_addr_rd64b = w; }
inline void SI::setPifAddrWr64b(word w)	{ data.pif_addr_wr64b = w; }
inline void SI::setStatus(word w)			{ data.status = w; }
inline void SI::setSpecialStatus(word w)	{ /*TODO*/ }

inline word SI::getDramAddr()				{ return data.dram_addr; }
inline word SI::getPifAddrRd64b()			{ return data.pif_addr_rd64b; }
inline word SI::getPifAddrWr64b()			{ return data.pif_addr_wr64b; }
inline word SI::getStatus()				{ return data.status; }
