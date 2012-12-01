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

#define VI_SEG_BEG					0x04400000
#define VI_SEG_END				0x044FFFFF

#define VI_STATUS_REG			0x04400000
#define VI_ORIGIN_REG			0x04400004
#define VI_WIDTH_REG			0x04400008
#define VI_INTR_REG				0x0440000C
#define VI_CURRENT_REG			0x04400010
#define VI_BURST_REG			0x04400014
#define VI_V_SYNC_REG			0x04400018
#define VI_H_SYNC_REG			0x0440001C
#define VI_LEAP_REG				0x04400020
#define VI_H_START_REG			0x04400024
#define VI_V_START_REG			0x04400028
#define VI_V_BURST_REG			0x0440002C
#define VI_X_SCALE_REG			0x04400030
#define VI_Y_SCALE_REG			0x04400034

//****************************************************************************
//** Video Interface (VI) Registers											**
//****************************************************************************

class VI : public MEM_SEG
{
public:
	VI();

	inline word getStatus();
	inline void setStatus(word);
	inline word getOrigin();
	inline void setOrigin(word);
	inline word getWidth();
	inline void setWidth(word);
	inline word getIntr();
	inline void setVintr(word);
	inline word getCurrent();
	inline void setCurrent(word);
	inline word getBurst();
	inline void setBurst(word);
	inline word getVsync();
	inline void setVsync(word);
	inline word getHsync();
	inline void setHsync(word);
	inline word getLeap();
	inline void setLeap(word);
	inline word getHstart();
	inline void setHstart(word);
	inline word getVstart();
	inline void setVstart(word);
	inline word getVburst();
	inline void setVburst(word);
	inline word getXscale();
	inline void setXscale(word);
	inline word getYscale();
	inline void setYscale(word);

private:
	struct	{
		word status;
		word origin;
		word width;
		word intr;
		word current;
		word burst;
		word v_sync;
		word h_sync;
		word leap;
		word h_start;
		word v_start;
		word v_burst;
		word x_scale;
		word y_scale;
		byte unused[0xFFFC8];
	} data;
};