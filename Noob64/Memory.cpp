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

#include "StdAfx.h"

//****************************************************************************
//** MEMORY																	**
//****************************************************************************

MEMORY::MEMORY(ROM* r) :
	rom			(*r),
	rdram		(*new RDRAM()),
	rdram_regs	(*new RDRAM_REGS()),
	sp_regs		(*new SP_REGS()),
	dpc_regs	(*new DPC_REGS()),
	dps_regs	(*new DPS_REGS()),
	mi_regs		(*new MI_REGS()),
	vi_regs		(*new VI_REGS()),
	ai_regs		(*new AI_REGS()),
	pi_regs		(*new PI_REGS()),
	ri_regs		(*new RI_REGS()),
	si_regs		(*new SI_REGS()),
	pif_rom		(*new PIF_ROM()),
	pif_ram		(*new PIF_RAM())
{
	memset(SRAM, 0, sizeof(SRAM));
	cic_chip = 0;
	check_intr = false;
}

void* MEMORY::operator[] (const word address)
{
	return virtual_to_physical(address);
}

//****************************************************************************
//** SEGMENTS																**
//****************************************************************************

#define INIT(data)					\
	memset(data, 0, sizeof(data));	\
	ptr = (char*) data;

MEM_SEG::MEM_SEG(word b, word e) : ptr(0), begining(b), end(e)					{}
MEM_SEG::~MEM_SEG()																{}
RDRAM::RDRAM() : MEM_SEG(RDRAM_SEG_BEGINING, RDRAM_SEG_END)						{ INIT(data) }
RDRAM_REGS::RDRAM_REGS() : MEM_SEG(RDRAM_REGS_SEG_BEGINING, RDRAM_REGS_SEG_END) { INIT(&data) }
SP_REGS::SP_REGS() : MEM_SEG(SP_SEG_BEGINING, SP_SEG_END)						{ INIT(&data) }
DPC_REGS::DPC_REGS() : MEM_SEG(DPC_SEG_BEGINING, DPC_SEG_END)					{ INIT(&data) }
DPS_REGS::DPS_REGS() : MEM_SEG(DPS_SEG_BEGINING, DPS_SEG_END)					{ INIT(&data) }
MI_REGS::MI_REGS() : MEM_SEG(MI_SEG_BEGINING, MI_SEG_END)						{ INIT(&data) }
VI_REGS::VI_REGS() : MEM_SEG(VI_SEG_BEGINING, VI_SEG_END)						{ INIT(&data) }
AI_REGS::AI_REGS() : MEM_SEG(AI_SEG_BEGINING, AI_SEG_END)						{ INIT(&data) }
PI_REGS::PI_REGS() : MEM_SEG(PI_SEG_BEGINING, PI_SEG_END)						{ INIT(&data) }
RI_REGS::RI_REGS() : MEM_SEG(RI_SEG_BEGINING, RI_SEG_END)						{ INIT(&data) }
SI_REGS::SI_REGS() : MEM_SEG(SI_SEG_BEGINING, SI_SEG_END)						{ INIT(&data) }
PIF_ROM::PIF_ROM() : MEM_SEG(PIF_ROM_SEG_BEGINING, PIF_ROM_SEG_END)				{ INIT(&data) }
PIF_RAM::PIF_RAM() : MEM_SEG(PIF_RAM_SEG_BEGINING, PIF_RAM_SEG_END)				{ INIT(&data) }

void* MEM_SEG::operator[] (const word address) const
{
	return (char*) ptr + address - begining;
}

bool is_address_defined(word address)
{
	if (KSEG0 <= address && address <= KSEG2-1)
		return true;
	// TODO
	/*
	dword i;
	for (i = 0; i < 64; i++)
	{
		if (FastTlb[i].ValidEntry == false)
			continue;
		if (address >= FastTlb[i].VSTART && address <= FastTlb[i].VEND)
			return true;
	}
	*/
	return false; 
}
