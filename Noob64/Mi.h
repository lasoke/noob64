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

#include "Memory.h"

#define MI_SEG_BEGINING			0x04300000
#define MI_SEG_END				0x043FFFFF

#define MI_INIT_MODE_REG		0x04300000
#define MI_VERSION_REG			0x04300004
#define MI_INTR_REG				0x04300008
#define MI_INTR_MASK_REG		0x0430000C

#define MI_CLR_INIT				0x0080
#define MI_SET_INIT				0x0100
#define MI_CLR_EBUS				0x0200
#define MI_SET_EBUS				0x0400
#define MI_CLR_DP_INTR			0x0800
#define MI_CLR_RDRAM			0x1000
#define MI_SET_RDRAM			0x2000

#define MI_MODE_INIT			0x0080
#define MI_MODE_EBUS			0x0100
#define MI_MODE_RDRAM			0x0200

#define MI_INTR_MASK_CLR_SP		0x0001
#define MI_INTR_MASK_SET_SP		0x0002
#define MI_INTR_MASK_CLR_SI		0x0004
#define MI_INTR_MASK_SET_SI		0x0008
#define MI_INTR_MASK_CLR_AI		0x0010
#define MI_INTR_MASK_SET_AI		0x0020
#define MI_INTR_MASK_CLR_VI		0x0040
#define MI_INTR_MASK_SET_VI		0x0080
#define MI_INTR_MASK_CLR_PI		0x0100
#define MI_INTR_MASK_SET_PI		0x0200
#define MI_INTR_MASK_CLR_DP		0x0400
#define MI_INTR_MASK_SET_DP		0x0800

#define MI_INTR_MASK_SP			0x01
#define MI_INTR_MASK_SI			0x02
#define MI_INTR_MASK_AI			0x04
#define MI_INTR_MASK_VI			0x08
#define MI_INTR_MASK_PI			0x10
#define MI_INTR_MASK_DP			0x20

#define MI_INTR_SP				0x01
#define MI_INTR_SI				0x02
#define MI_INTR_AI				0x04
#define MI_INTR_VI				0x08
#define MI_INTR_PI				0x10
#define MI_INTR_DP				0x20

//****************************************************************************
//** MIPS Interface (MI) Registers											**
//****************************************************************************

class MI_REGS : public MEM_SEG
{
public:
	MI_REGS();

	inline word getInitMode();
	inline void setInitMode(word);
	inline void setSpecialInitMode(word);
	inline word getVersion();
	inline void setVersion(word);
	inline word getIntr();
	inline void setIntr(word);
	inline word getIntrMask();
	inline void setIntrMask(word);
	inline void setSpecialIntrMask(word);

private:
	struct	{
		word init_mode;
		word version;
		word intr;
		word intr_mask;
		byte unused[0xFFFF0];
	} data;
};