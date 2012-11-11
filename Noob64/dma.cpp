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

void RCP::dma_pi_read()
{
	memcpy((char*) rom.ptr + (pi.getCartAddr() & 0xFFFFFFF),
		(char*) rdram.ptr + (pi.getDramAddr() & 0xFFFFFFF),
		(pi.getRdLen() & 0xFFFFFFF) + 1);
}

void RCP::dma_pi_write()
{
	memcpy((char*) rdram.ptr + (pi.getDramAddr() & 0xFFFFFFF),
		(char*) rom.ptr + (pi.getCartAddr() & 0xFFFFFFF),
		(pi.getWrLen() & 0xFFFFFFF) + 1);
}

void RCP::dma_sp_write()
{
	byte* mem = ((sp.getWrLen() & 0x1000) > 0) ? sp.getImem() : sp.getDmem();
	memcpy((char*) rdram.ptr + (sp.getDramAddr() & 0xFFFFFFF),
		mem + (sp.getMemAddr() & 0xFFF),
		(sp.getWrLen() & 0xFFF) + 1);
}

void RCP::dma_sp_read()
{
	byte* mem = ((sp.getRdLen() & 0x1000) > 0) ? sp.getImem() : sp.getDmem();
	memcpy(mem + (sp.getMemAddr() & 0xFFF),
		rdram.ptr + (sp.getDramAddr() & 0xFFFFFFF),
		(sp.getRdLen() & 0xFFF) + 1);
}

void RCP::dma_si_write()
{
	if (si.getPifAddrWr64b() != 0x1FC007C0)
		cout << "unknown SI use" << endl;
	memcpy((char*) rdram.ptr + (si.getDramAddr() & 0xFFFFFFF), (char*) pif_ram.ptr + (si.getPifAddrWr64b() & 0xFF), 64);

}

void RCP::dma_si_read()
{
	if (si.getPifAddrRd64b() != 0x1FC007C0)
		cout << "unknown SI use" << endl;
	memcpy((char*) pif_ram.ptr + (si.getPifAddrRd64b() & 0xFF), (char*) rdram.ptr + (si.getDramAddr() & 0xFFFFFFF), 64);
}