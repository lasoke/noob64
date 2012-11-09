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

// MEMORY SEGMENT
MEM_SEG::MEM_SEG() :
	ptr(0)
{
}

char* MEM_SEG::operator[] (const dword address) const
{
	return (char*) ptr + address;
}

//****************************************************************************
//** SEGMENTS CONSTRUCTORS					                                **
//****************************************************************************

// RDRAM
RDRAM::RDRAM()
{
	memset(data, 0, sizeof(data));
	ptr = (char*) data;
}

// RDRAM REGISTERS
RDRAM_REGS::RDRAM_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// SP REGISTERS
SP_REGS::SP_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// DPC REGISTERS
DPC_REGS::DPC_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// DPS REGISTERS
DPS_REGS::DPS_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// MI REGISTERS
MI_REGS::MI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// VI REGISTERS
VI_REGS::VI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// AI REGISTERS
AI_REGS::AI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// PI REGISTERS
PI_REGS::PI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// RI REGISTERS
RI_REGS::RI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// SI REGISTERS
SI_REGS::SI_REGS()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// PIF_ROM REGISTERS
PIF_ROM::PIF_ROM()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

// PIF_RAM REGISTERS
PIF_RAM::PIF_RAM()
{
	memset(&data, 0, sizeof(data));
	ptr = (char*) &data;
}

void MEMORY::dma_pi_read()
{
	memcpy(rom[0] + (pi_regs.getCartAddr() & 0xFFFFFFF),
		rdram[0] + (pi_regs.getDramAddr() & 0xFFFFFFF),
		(pi_regs.getRdLen() & 0xFFFFFFF) + 1);
}

void MEMORY::dma_pi_write()
{
	memcpy(rdram[0] + (pi_regs.getDramAddr() & 0xFFFFFFF),
		rom[0] + (pi_regs.getCartAddr() & 0xFFFFFFF),
		(pi_regs.getWrLen() & 0xFFFFFFF) + 1);
}

void MEMORY::dma_sp_write()
{
	if ((sp_regs.getWrLen() & 0x1000) > 0)
	{
		memcpy(rdram[0] + (sp_regs.getDramAddr() & 0xFFFFFFF),
			(sp_regs.getImem()) + (sp_regs.getMemAddr() & 0xFFF),
			(sp_regs.getWrLen() & 0xFFF) + 1);
	}
	else
	{
		memcpy(rdram[0] + (sp_regs.getDramAddr() & 0xFFFFFFF),
			sp_regs.getDmem() + (sp_regs.getMemAddr() & 0xFFF),
			(sp_regs.getWrLen() & 0xFFF) + 1);
	}
}

void MEMORY::dma_sp_read()
{
	if ((sp_regs.getRdLen() & 0x1000) > 0)
	{
		memcpy((sp_regs.getImem()) + (sp_regs.getMemAddr() & 0xFFF),
			rdram.ptr + (sp_regs.getDramAddr() & 0xFFFFFFF),
			(sp_regs.getRdLen() & 0xFFF) + 1);
	}
	else
	{
		memcpy(sp_regs.getDmem() + (sp_regs.getMemAddr() & 0xFFF),
			rdram.ptr + (sp_regs.getDramAddr() & 0xFFFFFFF),
			(sp_regs.getRdLen() & 0xFFF) + 1);
	}
}

void MEMORY::dma_si_write()
{
	if (si_regs.getPifAddrWr64b() != 0x1FC007C0)
	{
		cerr << "unknown SI use" << endl;
	}

	memcpy(rdram[0] + (si_regs.getDramAddr() & 0xFFFFFFF), pif_ram[0] + (si_regs.getPifAddrWr64b() & 0xFF), 64);
}

void MEMORY::dma_si_read()
{
	if (si_regs.getPifAddrRd64b() != 0x1FC007C0)
	{
		cerr << "unknown SI use" << endl;
	}

	memcpy(pif_ram[0] + (si_regs.getPifAddrRd64b() & 0xFF), rdram[0] + (si_regs.getDramAddr() & 0xFFFFFFF), 64);
}

bool is_address_defined(dword address)
{
	if (0x80000000 <= address && address <= 0xBFFFFFFF)
		return true;
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
