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

#include "Rsp.h"
#include "Gfx.h"
#include "Rom.h"
#include "Rdram.h"
#include "RdramRegs.h"
#include "Sp.h"
#include "Dpc.h"
#include "Dps.h"
#include "Ai.h"
#include "Mi.h"
#include "Vi.h"
#include "Pi.h"
#include "Ri.h"
#include "Si.h"
#include "PifRom.h"
#include "PifRam.h"

inline bool MEM_SEG::contains(word address) const			{ return begining <= address && address <= end; }

inline R4300i&		RCP::getCPU(void) const					{ return cpu; }
inline ROM&			RCP::getROM(void) const					{ return rom; }
inline RDRAM&		RCP::getRDRAM(void) const				{ return rdram; }
inline RDRAM_REGS&	RCP::getRdramRegs(void) const			{ return rdram_regs; }
inline SP&			RCP::getSP(void) const					{ return sp; }
inline DPC&			RCP::getDPC(void) const					{ return dpc; }
inline DPS&			RCP::getDPS(void) const					{ return dps; }
inline MI&			RCP::getMI(void) const					{ return mi; }
inline VI&			RCP::getVI(void) const					{ return vi; }
inline AI&			RCP::getAI(void) const					{ return ai; }
inline PI&			RCP::getPI(void) const					{ return pi; }
inline RI&			RCP::getRI(void) const					{ return ri; }
inline SI&			RCP::getSI(void) const					{ return si; }
inline PIF_ROM&		RCP::getPifRom(void) const				{ return pif_rom; }
inline PIF_RAM&		RCP::getPifRam(void) const				{ return pif_ram; }
inline RSP*			RCP::getRSP(void) const					{ return rsp; }
inline GFX*			RCP::getGFX(void) const					{ return gfx; }

inline bool RCP::isCheckInterrupt() const					{ return check_intr; }
inline void RCP::setCheckInterrupt(bool isCheckInterrupt)	{ check_intr = isCheckInterrupt; }





