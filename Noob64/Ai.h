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
 * The Ai files contains the functions, macro and structure to represente
 * and access the audio interface register of the n64 memory.
 *
 */

#pragma once

#include "Rcp.h"

#define AI_SEG_BEG				0x04500000
#define AI_SEG_END				0x045FFFFF

#define AI_DRAM_ADDR_REG		0x04500000
#define AI_LEN_REG				0x04500004
#define AI_CONTROL_REG			0x04500008
#define AI_STATUS_REG			0x0450000C
#define AI_DACRATE_REG			0x04500010
#define AI_BITRATE_REG			0x04500014

//****************************************************************************
//** Audio Interface (AI) Registers											**
//****************************************************************************

class AI : public MEM_SEG
{
public:
	AI();

	inline word getDramAddr();
	inline void setDramAddr(word);
	inline word getLen();
	inline void setLen(word);
	inline word getControl();
	inline void setControl(word);
	inline word getStatus();
	inline void setStatus(word);
	inline word getDacrate();
	inline void setDacrate(word);
	inline word getBitrate();
	inline void setBitrate(word);

private:
	struct {
		word dram_addr;
		word len;
		word control;
		word status;
		word dacrate;
		word bitrate;
		byte unused[0xFFFE8];
	} data;
};