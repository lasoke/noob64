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

/*
 * The PifRam files contains the functions, macro and structure to represente
 * and access the PifRam memory of the n64 memory.
 *
 */

#pragma once

#include "Rcp.h"

//****************************************************************************
//** PIF RAM																**
//****************************************************************************

#define PIF_RAM_SEG_BEG		0x1FC007C0
#define PIF_RAM_SEG_END		0x1FC007FF

#define CHL_LEN 0x20

class PIF_RAM : public MEM_SEG
{
public:
	PIF_RAM();
	void PifRamWrite(void);
private:
	struct {
		byte pram[0x40];
	} data;
	
};
