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

#define RI_SEG_BEGINING			0x04700000
#define RI_SEG_END				0x047FFFFF

#define RI_MODE_REG				0x04700000
#define RI_CONFIG_REG			0x04700004
#define RI_CURRENT_LOAD_REG		0x04700008
#define RI_SELECT_REG			0x0470000C
#define RI_REFRESH_REG			0x04700010
#define RI_LATENCY_REG			0x04700014
#define RI_RERROR_REG			0x04700018
#define RI_WERROR_REG			0x0470001C

//****************************************************************************
//** RDRAM Interface (RI) Registers											**
//****************************************************************************

class RI : public MEM_SEG
{
public:
	RI();

	inline word getMode();
	inline void setMode(word);
	inline word getConfig();
	inline void setConfig(word);
	inline word getCurrentLoad();
	inline void setCurrentLoad(word);
	inline word getSelect();
	inline void setSelect(word);
	inline word getRefresh();
	inline void setRefresh(word);
	inline word getLatency();
	inline void setLatency(word);
	inline word getRerror();
	inline void setRerror(word);
	inline word getWerror();
	inline void setWerror(word);

private:
	struct	{
		word mode;
		word config;
		word current_load;
		word select;
		word refresh;
		word latency;
		word rerror;
		word werror;
		byte unused[0xFFFE0];
	} data;
};