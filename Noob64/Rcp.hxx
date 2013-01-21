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

inline bool MEM_SEG::contains(word address) const	{ return begining <= address && address <= end; }

inline RDRAM*		RCP::getRDRAM(void)				{ return rdram; }
inline RDRAM_REGS*	RCP::getRdramRegs(void)			{ return rdram_regs; }
inline SP*			RCP::getSP(void)				{ return sp; }
inline DPC*			RCP::getDPC(void)				{ return dpc; }
inline DPS*			RCP::getDPS(void)				{ return dps; }
inline MI*			RCP::getMI(void)				{ return mi; }
inline VI*			RCP::getVI(void)				{ return vi; }
inline AI*			RCP::getAI(void)				{ return ai; }
inline PI*			RCP::getPI(void)				{ return pi; }
inline RI*			RCP::getRI(void)				{ return ri; }
inline SI*			RCP::getSI(void)				{ return si; }
inline PIF_ROM*		RCP::getPifRom(void)			{ return pif_rom; }
inline PIF_RAM*		RCP::getPifRam(void)			{ return pif_ram; }
inline ROM*			RCP::getROM(void)				{ return rom; }
inline byte*		RCP::getSRAM(void)				{ return SRAM; }

inline word			RCP::getViFieldNumber(void)		{ return vi_field_number; }
inline void			RCP::setViFieldNumber(word n)	{ vi_field_number = n; }

inline word			RCP::getViDelay(void)			{ return vi_delay; }
inline void			RCP::setViDelay(word n)			{ vi_delay = n; }






