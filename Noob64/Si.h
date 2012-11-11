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
 * chwing money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#pragma once

#include "Rcp.h"

#define SI_SEG_BEGINING			0x04800000
#define SI_SEG_END				0x048FFFFF

#define SI_DRAM_ADDR_REG		0x04800000
#define SI_PIF_ADDR_RD64B_REG	0x04800004
#define SI_PIF_ADDR_WR64B_REG	0x04800010
#define SI_STATUS_REG			0x04800018

#define	SI_STATUS_DMA_BUSY		0x0001
#define	SI_STATUS_RD_BUSY		0x0002
#define	SI_STATUS_DMA_ERROR		0x0008
#define	SI_STATUS_INTERRUPT		0x1000

//****************************************************************************
//** Serial Interface (SI) Registers										**
//****************************************************************************

class SI : public MEM_SEG
{
public:
	SI();

	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getPifAddrRd64b();
	inline void setPifAddrRd64b(word);
	inline word getPifAddrWr64b();
	inline void setPifAddrWr64b(word);
	inline word getStatus();
	inline void setStatus(word);
	inline void setSpecialStatus(word);

private:
	struct	{
		word dram_addr;
		word pif_addr_rd64b;
		word reserved;
		word reserved2;
		word pif_addr_wr64b;
		word reserved3;
		word status;
		byte unused[0xFFFE4];
	} data;
};
