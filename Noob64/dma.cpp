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
	memcpy((*rom)[ROM_SEG_BEG] + (pi->getCartAddr() & 0xFFFFFFF),
		(*rdram)[RDRAM_SEG_BEG] + (pi->getDramAddr() & 0xFFFFFFF),
		(pi->getRdLen() & 0xFFFFFFF) + 1);
	mi->setIntr(mi->getIntr() | MI_INTR_PI);
	pi->setStatus(pi->getStatus() & ~PI_STATUS_DMA_BUSY);
	R4300i::check_interrupt();
}

void RCP::dma_pi_write()
{
	memcpy((*rdram)[RDRAM_SEG_BEG] + (pi->getDramAddr() & 0xFFFFFFF),
		(*rom)[ROM_SEG_BEG] + (pi->getCartAddr() & 0xFFFFFFF),
		(pi->getWrLen() & 0xFFFFFFF) + 1);
	mi->setIntr(mi->getIntr() | MI_INTR_PI);
	pi->setStatus(pi->getStatus() & ~PI_STATUS_DMA_BUSY);
	R4300i::check_interrupt();
}

void RCP::dma_sp_write()
{
	byte* mem = ((sp->getMemAddr() & 0x1000) > 0) ? sp->getImem() : sp->getDmem();
	word* rdram_tmp = (word*)(*rdram)[RDRAM_SEG_BEG];
	for (unsigned int i = 0; i <= ((sp->getRdLen() & 0xFFF) / 4); i++)
	{
		rdram_tmp[((sp->getDramAddr() & 0xFFFFFFF) / 4) + i] = binary_to_type<word>(mem[((sp->getMemAddr() & 0xFFF) / 4) + i]);
	}
	/*memcpy((*rdram)[RDRAM_SEG_BEG] + (sp->getDramAddr() & 0xFFFFFFF),
		mem + (sp->getMemAddr() & 0xFFF),
		(sp->getWrLen() & 0xFFF) + 1);*/
}

void RCP::dma_sp_read()
{
	word* mem = ((sp->getMemAddr() & 0x1000) > 0) ? (word*) sp->getImem() : (word*) sp->getDmem();
	word* rdram_tmp = (word*)(*rdram)[RDRAM_SEG_BEG];
	for (unsigned int i = 0; i <= ((sp->getRdLen() & 0xFFF) / 4); i++)
	{
		mem[((sp->getMemAddr() & 0xFFF) / 4) + i] = type_to_binary<word>(rdram_tmp[((sp->getDramAddr() & 0xFFFFFFF) / 4) + i]);
	}
	/*memcpy(mem + (sp->getMemAddr() & 0xFFF),
		(*rdram)[RDRAM_SEG_BEG] + (sp->getDramAddr() & 0xFFFFFFF),
		(sp->getRdLen() & 0xFFF) + 1);*/

}

void RCP::dma_si_write()
{
	if (si->getPifAddrRd64b() != 0x1FC007C0)
		cout << "unknown SI use" << endl;
	memcpy((*rdram)[RDRAM_SEG_BEG] + (si->getDramAddr() & 0xFFFFFFF),
		(*pif_ram)[PIF_RAM_SEG_BEG], 64);
	mi->setIntr(mi->getIntr() | MI_INTR_SI);
	si->setStatus(si->getStatus() | SI_STATUS_INTERRUPT);
	R4300i::check_interrupt();
}

void RCP::dma_si_read()
{
	if (si->getPifAddrWr64b() != 0x1FC007C0)
		cout << "unknown SI use" << endl;
	memcpy((*pif_ram)[PIF_RAM_SEG_BEG],
		(*rdram)[RDRAM_SEG_BEG] + (si->getDramAddr() & 0xFFFFFFF), 64);
	pif_ram->PifRamWrite();
	mi->setIntr(mi->getIntr() | MI_INTR_SI);
	si->setStatus(si->getStatus() | SI_STATUS_INTERRUPT);
	R4300i::check_interrupt();
}
