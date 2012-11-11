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
#include "Mmu.h"


MMU::MMU(R4300i& cpu, RCP& rcp) : cpu(cpu), rcp(rcp) {}


MMU::~MMU(void) {}

void* MMU::operator[] (const word address)
{
	return virtual_to_physical(address);
}

void MMU::reset(void)
{
	for (int i = 0; i < 32; i++)
	{
		tlb[i].mask		= 0;
		tlb[i].vpn2		= 0;
		tlb[i].g		= 0;
		tlb[i].asid		= 0;
		tlb[i].pfn0		= 0;
		tlb[i].c0		= 0;
		tlb[i].d0		= 0;
		tlb[i].v0		= 0;
		tlb[i].pfn1		= 0;
		tlb[i].c1		= 0;
		tlb[i].d1		= 0;
		tlb[i].v1		= 0;
		tlb[i].r		= 0;
		tlb[i].start0	= 0;
		tlb[i].end0		= 0;
		tlb[i].phys0	= 0;
		tlb[i].start1	= 0;
		tlb[i].end1		= 0;
		tlb[i].phys1	= 0;
	}
	for (int i = 0; i < 0x100000; i++)
	{ 
		tlb_lut_r[i] = 0;
		tlb_lut_w[i] = 0;
	}
}

