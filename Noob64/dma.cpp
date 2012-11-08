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
		memcpy(rdram[0] + (sp_regs.getDramAddr() & 0xFFFFFFF),
			(sp_regs.getImem()) + (sp_regs.getMemAddr() & 0xFFF),
			(sp_regs.getWrLen() & 0xFFF) + 1);
	else
		memcpy(rdram[0] + (sp_regs.getDramAddr() & 0xFFFFFFF),
			sp_regs.getDmem() + (sp_regs.getMemAddr() & 0xFFF),
			(sp_regs.getWrLen() & 0xFFF) + 1);
}

void MEMORY::dma_sp_read()
{
	if ((sp_regs.getRdLen() & 0x1000) > 0)
		memcpy((sp_regs.getImem()) + (sp_regs.getMemAddr() & 0xFFF),
			rdram.ptr + (sp_regs.getDramAddr() & 0xFFFFFFF),
			(sp_regs.getRdLen() & 0xFFF) + 1);
	else
		memcpy(sp_regs.getDmem() + (sp_regs.getMemAddr() & 0xFFF),
			rdram.ptr + (sp_regs.getDramAddr() & 0xFFFFFFF),
			(sp_regs.getRdLen() & 0xFFF) + 1);
}

void MEMORY::dma_si_write()
{
	if (si_regs.getPifAddrWr64b() != 0x1FC007C0)
	{
		cerr << "unknown SI use" << endl;
	}

	memcpy(rdram[0] + (si_regs.getDramAddr() & 0xFFFFFFF),
		pif_ram[0] + (si_regs.getPifAddrWr64b() & 0xFF), 64);
}

void MEMORY::dma_si_read()
{
	if (si_regs.getPifAddrRd64b() != 0x1FC007C0)
	{
		cerr << "unknown SI use" << endl;
	}

	memcpy(pif_ram[0] + (si_regs.getPifAddrRd64b() & 0xFF),
		rdram[0] + (si_regs.getDramAddr() & 0xFFFFFFF), 64);
}
